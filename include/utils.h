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

# include <stdarg.h>
# include <stdlib.h>
# include <unistd.h>

# define DPRINTS_BUFFER_SIZE 1024

pid_t	create_zombie(void);

int		dprints(int fd, unsigned int argN, ...);
int		ft_strncmp(const char *s1, const char *s2, size_t n);

char	*pathjoin(const char *path, const char *filename);
char	*ft_itoa(int n);
char	*ft_strjoin(const char *s1, const char *s2);

size_t	ft_strlcat(char *dst, const char *src, size_t size);
size_t	ft_strlen(const char *s);

void	xsleep(unsigned int seconds);
void	free_array(char **array);

#endif
