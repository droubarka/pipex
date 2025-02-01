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

static void	init_childs(t_child *child, int nchilds, char **av, char **iofiles)
{
	int	xchild;
	int	last_stdin;

	xchild = 0;
	while (xchild < nchilds)
	{
		child->rank = xchild;
		child->cmdline = av[xchild + 1];
		if (init_stdio(child, nchilds, &last_stdin, iofiles) == -1)
		{
			close(last_stdin);
			break ;
		}
		if (setup_child(child) == -1)
		{
			close(last_stdin);
			close_stdio(child->stdio);
			break ;
		}
		close_stdio(child->stdio);
		xchild++;
	}
	free_array(child->path);
}

static int	wait_childs(int total_childs)
{
	int	xchild;

	xchild = 0;
	while (xchild < total_childs)
	{
		if (wait(NULL) == -1)
			return (EXIT_FAILURE);
		xchild++;
	}
	return (EXIT_SUCCESS);
}

int	pipex(int ac, char **av, char **envp)
{
	int		total_childs;
	char	*iofiles[2];
	t_child	child;

	iofiles[0] = av[0];
	iofiles[1] = av[ac - 1];
	child.envp = envp;
	child.path = get_path(envp);
	if (child.path == NULL)
		return (EXIT_FAILURE);
	total_childs = ac - 2;
	init_childs(&child, total_childs, av, iofiles);
	return (wait_childs(total_childs));
}
