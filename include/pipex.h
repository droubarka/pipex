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

# ifndef ARG_MAX
# define ARG_MAX (1 << 21)
# endif

# ifndef WARN_MAX
# define WARN_MAX (PATH_MAX + ARG_MAX + 128)
# endif

//typedef struct s_other {
//
//};

typedef struct s_child {
	int		rank;
	int		stdio[2];
	char	*cmdline;
	char	**envp;
	char	**path;

	char	*iofiles[2];
	int		oflag;
}	t_child;

int		pipex(int ac, char **av, char **envp, int upstream);
int		init_stdio(t_child *child, int nchilds, int *upstream);
pid_t	create_child(t_child *child, int last_stdin);
int		execute_child(t_child *child);

void	xsleep(unsigned int seconds);
char	*pathjoin(char *path, char *filename);
void	close_stdio(int *stdio);
void	free_array(char **array);
int		terminate(char *s, int status);

int		heredoc(char *argv_0, char *limiter);

#endif
