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

# include "../libft/libft.h"

typedef struct s_child {
	int		rank;
	int		stdio[2];
	char	**path;
	char	**envp;
	char	*cmdline;
}	t_child;

int	pipex(int ac, char **av, char **envp);
int	init_stdio(t_child *child, int n_childs, int *upstream, char **iofiles);
int	setup_child(t_child *child);
void	execute_child(t_child *child);

void	close_stdio(int *stdio);
void	free_array(char **array);
void	terminate(char *s, int status);

void	xsleep(unsigned int seconds);
char	*pathjoin(char *path, char *filename);

#endif

/*
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <sys/wait.h>
# include "../libft/libft.h"


void	terminate(char *s, int status);

//int		setup_stdio(t_child *child, int n_childs, int *upstream, char **iofiles);
int		setup_child(t_child *child);
void	execute_child(t_child *child);

void	free_array(char **array);
void	close_stdio(int *stdio);
void	xsleep(unsigned int seconds);
char	*pathjoin(char *path, char *filename);

#endif
*/
