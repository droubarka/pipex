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

static void	init_iofiles(int *iofiles, char *infile, char *outfile)
{
	iofiles[0] = open(infile, O_RDONLY);
	if (iofiles[0] == -1)
		terminate("pipex: %errno: infile", -1);

	iofiles[1] = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (iofiles[1] == -1)
		terminate("pipex: %errno: outfile", -1);
}

static int	init_stdio(int *stdio, int xchild, int nchilds, int *iofiles)
{
	if (xchild != 0 && xchild != nchilds - 1)
		return (pipe(stdio) != -1);

	if (xchild == 0)
		stdio[0] = iofiles[0];

	if (xchild == nchilds - 1)
		stdio[1] = iofiles[1];

	return (1);
}

void	exec_child(char *cmd, char **path, char **envp)
{}

void	init_child(char *cmdline, int *stdio, char **path, char **envp)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		dup2(stdio[0], STDIN_FILENO);
		dup2(stdio[1], STDOUT_FILENO);

		close(stdio[0]);
		close(stdio[1]);

		exec_child(cmd, path, envp);
		terminate("execve", EXIT_FAILURE);
	}
	else if (pid == -1)
	{
		close(stdio[0]);
		close(stdio[1]);
	}
}

int	pipex(int ac, char **av, char **envp)
{
	int		iofiles[2];
	int		stdio[2];
	int		nchilds;
	int		xchild;
	char	**path;

	init_iofiles(iofiles, av[0], av[ac - 1]);

	path = get_path(envp);
	nchilds = ac - 2;

	xchild = 0;
	while (xchild < nchilds)
	{
		if (init_stdio(stdio, xchild, nchilds, iofiles))
		{
			if (xchild == 0)
			{
				
			}
			else
			{
				
			}
		}
		else
		{
		}
//		init_child(av[xchild + 1], stdio, path, envp);
		xchild++;
	}

	xchild = 0;
	while (xchild < nchilds)
	{
		wait(NULL);
		xchild++;
	}

	return (EXIT_SUCCESS);
}
