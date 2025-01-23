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

static void	init_stdio(t_child *child, int total_childs, int *last_stdin, char **iofiles)
{
	int pipefd[2];
	int	infile;
	int	outfile;

	if (child->rank == 0)
	{
		infile = open(iofiles[0], O_RDONLY);
		if (infile == -1)
			terminate("pipex: %errno: infile", -1);
		*last_stdin = infile;
	}

	if (child->rank != total_childs - 1)
	{
		pipe(pipefd); //?

		child->stdio[0] = *last_stdin;
		child->stdio[1] = pipefd[1];
		*last_stdin = pipefd[0];
	}
	else
	{
		outfile = open(iofiles[1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (outfile == -1)
			terminate("pipex: %errno: outfile", -1);
		child->stdio[0] = *last_stdin;
		child->stdio[1] = outfile;
	}
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

		init_stdio(&curr_child, total_childs, &last_stdin, iofiles);

//		init_child();
//		exec_child();

//		close(stdio[0]);
//		close(stdio[1]);
		xchild++;
	}
}
