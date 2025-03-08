/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-oub <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 17:34:47 by mait-oub          #+#    #+#             */
/*   Updated: 2024/10/26 17:34:49 by mait-oub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

char	*ft_strjoin(const char *s1, const char *s2)
{
	char	*sj;
	size_t	s1_len;
	size_t	s2_len;
	size_t	sj_len;

	sj = NULL;
	if (s1 && s2)
	{
		s1_len = ft_strlen(s1);
		s2_len = ft_strlen(s2);
		sj_len = s1_len + s2_len;
		sj = malloc(sizeof(char) * (sj_len + 1));
		if (sj)
		{
			*sj = 0;
			ft_strlcat(sj, s1, sj_len + 1);
			ft_strlcat(sj, s2, sj_len + 1);
		}
	}
	return (sj);
}
