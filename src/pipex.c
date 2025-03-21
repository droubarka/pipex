/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-oub <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 09:57:46 by mait-oub          #+#    #+#             */
/*   Updated: 2025/01/22 09:57:52 by mait-oub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	**get_path(char **envp)
{
	if (envp != NULL)
	{
		while (*envp)
		{
			if (!ft_strncmp(*envp, "PATH=", 5))
			{
				return (ft_split(*envp + 5, ':'));
			}
			envp++;
		}
	}
	return (ft_split("", ':'));
}

static int	wait_childs(pid_t last_child)
{
	pid_t	pid;
	int		stat_loc;
	int		exit_status;

	exit_status = EXIT_FAILURE;
	while (1)
	{
		pid = wait(&stat_loc);
		if (pid == -1)
			break ;
		else if (pid == last_child)
		{
			if (WIFEXITED(stat_loc))
				exit_status = WEXITSTATUS(stat_loc);
			else if (WIFSIGNALED(stat_loc))
				exit_status = WCOREDUMP(stat_loc) | WTERMSIG(stat_loc);
		}
	}
	if (last_child == -1)
		exit_status = 254;
	return (exit_status);
}

static pid_t	create_childs(t_pipeline *pipeline, int last_stdin)
{
	t_child	*child;
	pid_t	last_child_pid;

	child = &pipeline->current_child;
	pipeline->current_child_rank = 0;
	while (pipeline->current_child_rank < pipeline->total_childs)
	{
		last_child_pid = 0;
		child->cmdline = pipeline->cmdlines[pipeline->current_child_rank];
		if (init_stdio(pipeline, &last_stdin) == -1)
			break ;
		last_child_pid = create_child(pipeline, last_stdin);
		if (last_child_pid == -1)
		{
			close_stdio(child->stdio);
			break ;
		}
		close_stdio(child->stdio);
		pipeline->current_child_rank++;
	}
	if (last_stdin != -1)
		close(last_stdin);
	free_array(pipeline->splited_path);
	return (last_child_pid);
}

int	pipex(int ac, char **av, char **envp, int upstream)
{
	t_pipeline	pipeline;
	t_child		*child;
	pid_t		last_child_pid;
	int			exit_status;

	pipeline.total_childs = ac - 2;
	child = &pipeline.current_child;
	child->envp = envp;
	pipeline.splited_path = get_path(envp);
	pipeline.cmdlines = av + 1;
	pipeline.iofiles[0] = av[0];
	pipeline.iofiles[1] = av[ac - 1];
	pipeline.oflag = O_WRONLY | O_CREAT;
	if (upstream != -1)
		pipeline.oflag |= O_APPEND;
	else
		pipeline.oflag |= O_TRUNC;
	if (pipeline.splited_path == NULL)
	{
		terminate("malloc", -1);
		return (EXIT_FAILURE);
	}
	last_child_pid = create_childs(&pipeline, upstream);
	exit_status = wait_childs(last_child_pid);
	return (exit_status);
}
