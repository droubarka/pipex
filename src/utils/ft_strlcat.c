/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-oub <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 17:26:06 by mait-oub          #+#    #+#             */
/*   Updated: 2024/10/23 17:26:09 by mait-oub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	src_len;
	size_t	dst_len;

	src_len = ft_strlen(src);
	dst_len = ft_strlen(dst);
	if (dst_len < size)
	{
		dst += dst_len;
		while (dst_len + 1 < size-- && *src)
		{
			*dst++ = *src++;
		}
		*dst = '\0';
		return (src_len + dst_len);
	}
	return (src_len + size);
}
