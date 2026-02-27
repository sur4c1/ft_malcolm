/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyyyyy <yyyyyy@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 11:18:17 by yyyyyy            #+#    #+#             */
/*   Updated: 2026/02/25 15:20:48 by yyyyyy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdarg.h>
#include "ft_error.h"

int ft_error(t_err errcode, ...)
{
	const char errmsg[][128] = {
		[ERR_OK] = "",
		[ERR_USAGE] = "Usage: %s <source IP> <source MAC> <target IP> <targete MAC>\n",
		[ERR_INVALID_TARGET_IP] = "Unkwown host or invalid IP: %s\n",
		[ERR_NO_INTERFACE] = "No interface found for host/IP %s\n",
		[ERR_NO_INTERFACE_IDX] = "Failed to get interface index: %s\n",
		[ERR_NO_SOCKET] = "Failed to create socket: %s\n",
		[ERR_NO_BIND] = "Failed to bind socket: %s\n",
		[ERR_NO_RECV] = "recvfrom() failed: %s\n",
	};
	va_list args;

	va_start(args, errcode);
	vprintf(errmsg[errcode], args);
	va_end(args);
	return (errcode);
}
