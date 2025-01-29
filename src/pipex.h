/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-oub <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 00:16:26 by mait-oub          #+#    #+#             */
/*   Updated: 2025/01/27 00:16:28 by mait-oub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/wait.h>

#include "../libft/libft.h"


#ifndef PIPEX_H
#define PIPEX_H

int	pipex(int ac, char **av, char **envp);

typedef struct	s_child {
	int		rank;
	int		stdio[2];
	char	**path;
	char	**envp;
	char	*cmdline;
} t_child;

void	terminate(const char *s, int status);
void	free_all(char **av);
pid_t	retry_call(pid_t (*func)(void), int x);
char	**get_path(char **envp);

#endif
