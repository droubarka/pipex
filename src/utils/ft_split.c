/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-oub <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 02:46:29 by mait-oub          #+#    #+#             */
/*   Updated: 2025/03/15 02:46:32 by mait-oub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

static size_t	countwords(const char *s, char c)
{
	size_t	counter;

	counter = 0;
	while (*s)
	{
		while (*s && *s == c)
		{
			s++;
		}
		if (*s)
		{
			counter++;
			while (*s && *s != c)
			{
				s++;
			}
		}
	}
	return (counter);
}

static void	cleanup(char **splited_str)
{
	char	**root;

	root = splited_str;
	while (*splited_str != NULL)
	{
		free(*splited_str);
		splited_str++;
	}
	free(root);
}

static void	fill(char **splited_str, size_t *idx, char *first_ptr, size_t size)
{
	splited_str[*idx][0] = 0;
	ft_strlcat(splited_str[*idx], first_ptr, size);
	(*idx)++;
}

static void	skip(char **s, char c)
{
	while (**s && **s != c)
	{
		(*s)++;
	}
}

char	**ft_split(const char *s, char c)
{
	char	**splited_str;
	char	*first_ptr;
	size_t	current_str_size;
	size_t	idx;

	splited_str = malloc(sizeof(char *) * (countwords(s, c) + 1));
	if (splited_str == NULL)
		return (NULL);
	idx = 0;
	while (*s)
	{
		while (*s && *s == c)
			s++;
		if (*s)
		{
			first_ptr = (char *) s;
			skip((char **) &s, c);
			current_str_size = (s - first_ptr) + 1;
			splited_str[idx] = malloc(sizeof(char) * current_str_size);
			if (splited_str[idx] == NULL)
				return (cleanup(splited_str), NULL);
			fill(splited_str, &idx, first_ptr, current_str_size);
		}
	}
	return (splited_str[idx] = NULL, splited_str);
}
