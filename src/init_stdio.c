/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_stdio.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-oub <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 09:57:46 by mait-oub          #+#    #+#             */
/*   Updated: 2025/02/01 00:08:05 by mait-oub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	init_stdio_lastone(t_pipeline *pipeline, int *upstream)
{
	t_child	*child;

	child = &pipeline->current_child;
	child->stdio[0] = *upstream;
	*upstream = -1;
	child->stdio[1] = open(pipeline->iofiles[1], pipeline->oflag, 0644);
	if (child->stdio[1] == -1)
	{
		return (-1);
	}
	return (0);
}

int	init_stdio(t_pipeline *pipeline, int *upstream)
{
	t_child	*child;
	int		pipefd[2];

	child = &pipeline->current_child;
	if (pipeline->current_child_rank == 0 && *upstream == -1)
	{
		*upstream = open(pipeline->iofiles[0], O_RDONLY);
		if (*upstream == -1)
			terminate(pipeline->iofiles[0], -1);
	}
	if (pipeline->current_child_rank == pipeline->total_childs - 1)
	{
		if (init_stdio_lastone(pipeline, upstream) == -1)
			terminate(pipeline->iofiles[1], -1);
		return (0);
	}
	if (pipe(pipefd) == -1)
	{
		terminate("pipe", -1);
		return (-1);
	}
	child->stdio[0] = *upstream;
	child->stdio[1] = pipefd[1];
	*upstream = pipefd[0];
	return (0);
}
