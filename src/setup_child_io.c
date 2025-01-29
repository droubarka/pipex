/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_child_io.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-oub <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 09:57:46 by mait-oub          #+#    #+#             */
/*   Updated: 2025/01/29 09:22:37 by mait-oub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	setup_last_child_io(t_child *child, int *upstream, char *outfile)
{
	child->stdio[0] = *upstream;
	child->stdio[1] = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (child->stdio[1] == -1)
		terminate(outfile, -1);
	*upstream = -1;
	return (0);
}

int	setup_child_io(t_child *child, int n_childs, int *upstream, char **iofiles)
{
	int	pipefd[2];

	if (child->rank == 0)
	{
		*upstream = open(iofiles[0], O_RDONLY);
		if (*upstream == -1)
			terminate(iofiles[0], -1);
	}
	if (child->rank == n_childs - 1)
	{
		setup_last_child_io(child, upstream, iofiles[1]);
		return (0);
	}
	if (pipe(pipefd) == -1)
	{
		terminate("pipe error", -1);
		return (-1);
	}
	child->stdio[0] = *upstream;
	child->stdio[1] = pipefd[1];
	*upstream = pipefd[0];
	return (0);
}
