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
		if (pid == -1)
			break ;
		else if (pid == last_child)
		{
			if (WIFEXITED(stat_loc))
				exit_status = WEXITSTATUS(stat_loc);
			else
				exit_status = WTERMSIG(stat_loc);
		}
	}
//	if (last_child == -1)
//		return (-1);
//	else if (last_child == 0)
//		return (-1);
	return (exit_status);
}

static int	init_childs(t_child *child, int nchilds, char **av, int last_stdin)
{
	int		xchild;
	pid_t	last_child;

	xchild = 0;
	last_child = 0;
	while (xchild < nchilds)
	{
		child->rank = xchild;
		child->cmdline = av[xchild + 1];
		if (init_stdio(child, nchilds, &last_stdin) == -1)
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

int	pipex(int ac, char **av, char **envp, int upstream)
{
	int		total_childs;
	int		exit_status;
	t_child	child;

	child.path = get_path(envp);
	if (child.path == NULL)
		return (EXIT_FAILURE);
	child.envp = envp;
	child.iofiles[0] = av[0];
	child.iofiles[1] = av[ac - 1];
	total_childs = ac - 2;
	exit_status = init_childs(&child, total_childs, av, upstream);
	return (exit_status);
}
