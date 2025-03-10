// Fri Feb 21 05:58:07 PM EST 2025

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

char	**ft_split(const char *s, char c)
{
	char	**splited_str;
	char	*first_ptr;
	size_t	current_str_size;
	size_t	idx;

	if (s == NULL)
		return (NULL);
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
			while (*s && *s != c)
				s++;
			current_str_size = (s - first_ptr) + 1;
			splited_str[idx] = malloc(sizeof(char) * current_str_size);
			if (splited_str[idx] == NULL)
			{
				cleanup(splited_str);
				return (NULL);
			}
			splited_str[idx][0] = 0;
			ft_strlcat(splited_str[idx], first_ptr, current_str_size);
			idx++;
		}
	}
	splited_str[idx] = NULL;
	return (splited_str);
}
