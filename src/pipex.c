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

int	init_stdio(t_child *child, int total_childs, int *last_stdin, char **iofiles)
{
	int pipefd[2];

	if (child->rank == 0)
	{
		*last_stdin = open(iofiles[0], O_RDONLY);
		if (*last_stdin == -1)
			terminate("pipex: %infile", -1); //?
	}
	if (child->rank != total_childs - 1)
	{
		if (pipe(pipefd) == -1)
		{
			terminate("pipex: pipe", -1); //?
			return (-1);
		}
		child->stdio[0] = *last_stdin;
		child->stdio[1] = pipefd[1];
		*last_stdin = pipefd[0];
	}
	else
	{
		child->stdio[0] = *last_stdin;
		child->stdio[1] = open(iofiles[1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (child->stdio[1] == -1)
			terminate("pipex: %outfile", -1); //?
	}
	return (0);
}

int	exec_child(t_child child)
{
}

int	init_child(t_child child)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		if (dup2(child->stdio[0], STDIN_FILENO) == -1) //?
			close(STDIN_FILENO);
		close(child->stdio[0]);

		if (dup2(child->stdio[1], STDOUT_FILENO) == -1) //?
			close(STDOUT_FILENO);
		close(child->stdio[1]);

		if (exec_command(child) == -1)
		{
			
		}
	}
	else if (pid == -1)
	{
		terminate("pipex: fork", -1); //?
		return (-1);
	}
	return (0);
}

int	pipex(int ac, char **av, char **envp)
{
	int		total_childs;
	int		last_stdin;
	int		xchild;
	char	*iofiles[2];
	t_child	curr_child;

	curr_child.path = get_path(envp);
	curr_child.envp = envp;

	iofiles[0] = av[0];
	iofiles[1] = av[ac - 1];

	total_childs = ac - 2;

	xchild = 0;
	while (xchild < total_childs)
	{
		curr_child.rank = xchild;
		curr_child.cmd = av[xchild + 1];

		if (init_stdio(&curr_child, total_childs, &last_stdin, iofiles) == -1)
		{
			close(last_stdin);
			break ;
		}

		if (init_child(curr_child) == -1)
		{
			close(last_stdin);
			break ;
		}

		close(curr_child.stdio[0]);
		close(curr_child.stdio[1]);

		xchild++;
	}

	// free(path);

	xchild = 0;
	while (xchild < total_childs)
	{
		wait(NULL);
		xchild++;
	}
}
