/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-oub <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 21:08:24 by mait-oub          #+#    #+#             */
/*   Updated: 2025/02/18 23:14:57 by mait-oub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "utils.h"

# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <stdio.h>
# include <sys/wait.h>

# define TERMINATE_BUFFER_SIZE PATH_MAX + 128

typedef struct s_pipeline	t_pipeline;
typedef struct s_child		t_child;
typedef struct s_execute	t_execute;

struct s_execute {
	char	*pathname;
	char	**argv;
	char	**envp;
};

struct s_child {
	int		stdio[2];
	char	*cmdline;
	char	**envp;
};

struct s_pipeline {
	int		total_childs;
	int		current_child_rank;
	t_child	current_child;
	char	**splited_path;
	char	**cmdlines;
	char	*iofiles[2];
	int		oflag;
};

int	heredoc(const char *argv_0, const char *delimiter);

int	pipex(int ac, char **av, char **envp, int upstream);
int	init_stdio(t_pipeline *pipeline, int *upstream);

pid_t	create_child(t_pipeline *pipeline, int last_stdin);

int	execute_child(t_pipeline *pipeline);
int	close_stdio(int *stdio);
int	terminate(const char *s, int status);

#endif
