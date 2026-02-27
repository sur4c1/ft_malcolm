/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malcolm.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyyyyy <yyyyyy@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 11:15:54 by yyyyyy            #+#    #+#             */
/*   Updated: 2026/02/25 15:26:17 by yyyyyy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

#include <arpa/inet.h>
#include <sys/socket.h>
#include <ifaddrs.h>
#include <stdio.h>
#include <net/if.h>
#include <linux/if_ether.h>
#include <linux/if_arp.h>
#include <string.h>
#include <errno.h>

#include "ft_error.h"
#include "libft.h"

static struct ifaddrs *find_target_interface(struct sockaddr_in sa_target)
{
	struct ifaddrs *ifa;
	struct sockaddr_in *sa_addr;
	struct sockaddr_in *sa_mask;

	getifaddrs(&ifa);
	while (ifa)
	{
		if (ifa->ifa_addr && ifa->ifa_addr->sa_family == AF_INET)
		{
			sa_addr = (struct sockaddr_in *)ifa->ifa_addr;
			sa_mask = (struct sockaddr_in *)ifa->ifa_netmask;
			if ((sa_target.sin_addr.s_addr & sa_mask->sin_addr.s_addr) == (sa_addr->sin_addr.s_addr & sa_mask->sin_addr.s_addr))
			{
				printf("Found available interface: %s\n", ifa->ifa_name);
				return (ifa);
			}
		}
		ifa = ifa->ifa_next;
	}
	freeifaddrs(ifa);
	return (NULL);
}

int main(int argc, char *argv[])
{
	struct ifaddrs *target_ifa;
	struct sockaddr_in sa_target;
	struct sockaddr_ll if_address;
	unsigned int interface_idx;
	int sockfd;
	char buff[1014];
	ssize_t len;

	if (argc != 5)
		return (ft_error(ERR_USAGE, argv[0]));

	if (!inet_pton(AF_INET, argv[3], &sa_target.sin_addr))
		return (ft_error(ERR_INVALID_TARGET_IP, argv[3]));
	target_ifa = find_target_interface(sa_target);
	if (!target_ifa)
		return (ft_error(ERR_NO_INTERFACE, argv[3]));
	interface_idx = if_nametoindex(target_ifa->ifa_name);
	if (!interface_idx)
		return (ft_error(ERR_NO_INTERFACE_IDX, strerror(errno)));
	printf("Interface index is %d\n", interface_idx);
	sockfd = socket(AF_PACKET, SOCK_RAW, ETH_P_ARP);
	if (sockfd < 0)
		return (ft_error(ERR_NO_SOCKET, strerror(errno)));
	ft_bzero(&if_address, sizeof(if_address));
	if_address.sll_ifindex = interface_idx;
	if_address.sll_family = AF_PACKET;
	if (bind(sockfd, (struct sockaddr *)&if_address, sizeof(struct sockaddr_ll)) < 0)
		return (ft_error(ERR_NO_BIND, strerror(errno)));
	while (1)
	{
		len = recvfrom(sockfd, buff, sizeof(buff), 0, NULL, NULL);
		printf("eheheh %zd\n", len);
		if (len < 0)
			return (ft_error(ERR_NO_RECV, strerror(errno)));
	}
	(void)argv;
}
