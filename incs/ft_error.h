/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyyyyy <yyyyyy@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 11:22:48 by yyyyyy            #+#    #+#             */
/*   Updated: 2026/02/25 15:20:04 by yyyyyy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/// @brief Error codes
typedef enum e_err
{
	ERR_OK,
	ERR_USAGE,
	ERR_INVALID_TARGET_IP,
	ERR_NO_INTERFACE,
	ERR_NO_INTERFACE_IDX,
	ERR_NO_SOCKET,
	ERR_NO_BIND,
	ERR_NO_RECV,
} t_err;

/// @brief Print the error message for the error code
/// @param errcode The error code
/// @return The error code
int ft_error(t_err errcode, ...);
