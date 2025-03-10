/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-oub <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 03:05:10 by mait-oub          #+#    #+#             */
/*   Updated: 2025/03/08 03:05:12 by mait-oub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "get_next_line.h"

# include <limits.h>
# include <stdarg.h>
# include <stdlib.h>
# include <unistd.h>

# ifndef ARG_MAX
# define ARG_MAX (1 << 21)
# endif

# ifndef DPRINTS_BUFFER_SIZE
# define DPRINTS_BUFFER_SIZE (ARG_MAX + 64)
# endif

pid_t	create_zombie(void);

int	dprints(int fd, unsigned int argN, ...);
int	free_array(char **array);
int	ft_strncmp(const char *s1, const char *s2, size_t n);

char	*ft_itoa(int n);
char	**ft_split(const char *s, char c);
char	*ft_strchr(const char *s, int c);
char	*ft_strjoin(const char *s1, const char *s2);
char	*pathjoin(const char *path, const char *filename);

size_t	ft_strlcat(char *dst, const char *src, size_t size);
size_t	ft_strlen(const char *s);

void	xsleep(unsigned int seconds);

#endif
