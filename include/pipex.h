/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-oub <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 21:08:24 by mait-oub          #+#    #+#             */
/*   Updated: 2025/01/29 21:09:25 by mait-oub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <errno.h>
# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <limits.h>

# include "../libft/libft.h"
# include "../get_next_line/get_next_line.h"

typedef struct s_child {
	int		rank;
	int		stdio[2];
	char	**path;
	char	**envp;
	char	*cmdline;

	char	*iofiles[2];

}	t_child;

int		pipex(int ac, char **av, char **envp, int upstream);
int		init_stdio(t_child *child, int n_childs, int *upstream);
pid_t	setup_child(t_child *child, int last_stdin);
void	execute_child(t_child *child);

void	xsleep(unsigned int seconds);
char	*pathjoin(char *path, char *filename);
void	close_stdio(int *stdio);
void	free_array(char **array);
void	terminate(char *s, int status);

int		heredoc(char *limiter);

#endif
