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

typedef struct s_pipeline	t_pipeline;
typedef struct s_child		t_child;
typedef struct s_execute	t_exec;

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
	char	*iofiles[2];
	int		oflag;
};

#endif
