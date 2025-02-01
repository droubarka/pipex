/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_child.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-oub <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 09:57:46 by mait-oub          #+#    #+#             */
/*   Updated: 2025/01/30 04:40:38 by mait-oub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static pid_t	retry_fork(unsigned int max_retries)
{
	pid_t	pid;
	int		seconds;

	seconds = 1;
	while (max_retries--)
	{
		pid = fork();
		if (pid != -1)
			return (pid);
		terminate("fork: retry", -1);
		xsleep(seconds);
		seconds *= 2;
	}
	terminate("fork", -1);
	return (-1);
}

static int	setup_stdio(t_child *child)
{
	int	stdio[2];

	stdio[0] = STDIN_FILENO;
	stdio[1] = STDOUT_FILENO;
	if (dup2(child->stdio[0], stdio[0]) == -1)
	{
		free_array(child->path);
		close_stdio(child->stdio);
		terminate(NULL, EXIT_FAILURE);
	}
	if (dup2(child->stdio[1], stdio[1]) == -1)
	{
		free_array(child->path);
		close_stdio(child->stdio);
		close(stdio[0]);
		terminate(NULL, EXIT_FAILURE);
	}
	close_stdio(child->stdio);
	child->stdio[0] = stdio[0];
	child->stdio[1] = stdio[1];
	return (0);
}

int	setup_child(t_child *child, int last_stdin)
{
	pid_t	pid;

	pid = retry_fork(4);
	if (pid == -1)
		return (-1);
	if (pid == 0)
	{
		close(last_stdin);
		setup_stdio(child);
		execute_child(child);
	}
	return (0);
}
