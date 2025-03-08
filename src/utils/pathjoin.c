/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathjoin.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-oub <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 00:00:56 by mait-oub          #+#    #+#             */
/*   Updated: 2025/03/08 03:45:25 by mait-oub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

char	*pathjoin(const char *path, const char *filename)
{
	char	*pathname;
	char	*temp;

	pathname = ft_strjoin(path, "/");
	if (pathname != NULL)
	{
		temp = pathname;
		pathname = ft_strjoin(pathname, filename);
		free(temp);
	}
	return (pathname);
}
