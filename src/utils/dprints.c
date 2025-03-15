/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dprints.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-oub <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 00:00:56 by mait-oub          #+#    #+#             */
/*   Updated: 2025/03/08 03:11:52 by mait-oub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

int	dprints(int fd, unsigned int argN, ...)
{
	char	buffer[DPRINTS_BUFFER_SIZE];
	va_list	ap;

	*buffer = 0;
	va_start(ap, argN);
	while (argN--)
	{
		ft_strlcat(buffer, va_arg(ap, char *), DPRINTS_BUFFER_SIZE);
	}
	va_end(ap);
	write(fd, buffer, ft_strlen(buffer));
	return (1);
}
