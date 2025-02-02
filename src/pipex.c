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
	while (*envp)
	{
		if (!ft_strncmp(*envp, "PATH=", 5))
			return (ft_split(*envp + 5, ':'));
		envp++;
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
		if (pid == last_child)
		{
			if (WIFEXITED(stat_loc))
				exit_status = WEXITSTATUS(stat_loc);
			else
				exit_status = WTERMSIG(stat_loc);
		}
		else if (pid == -1)
			break ;
	}
	return (exit_status);
}

static int	init_childs(t_child *child, int nchilds, char **av, char **iofiles)
{
	int		xchild;
	int		last_stdin;
	pid_t	last_child;

	xchild = 0;
	while (xchild < nchilds)
	{
		child->rank = xchild;
		child->cmdline = av[xchild + 1];
		if (init_stdio(child, nchilds, &last_stdin, iofiles) == -1)
			break ;
		last_child = setup_child(child, last_stdin);
		if (last_child == -1)
		{
			close_stdio(child->stdio);
			break ;
		}
		close_stdio(child->stdio);
		xchild++;
	}
	if (last_stdin != -1)
		close(last_stdin);
	free_array(child->path);
	return (wait_childs(last_child));
}

int	pipex(int ac, char **av, char **envp)
{
	int		total_childs;
	int		exit_status;
	char	*iofiles[2];
	t_child	child;

	iofiles[0] = av[0];
	iofiles[1] = av[ac - 1];
	child.envp = envp;
	child.path = get_path(envp);
	if (child.path == NULL)
		return (EXIT_FAILURE);
	total_childs = ac - 2;
	exit_status = init_childs(&child, total_childs, av, iofiles);
	return (exit_status);
}
