/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_child.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-oub <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 09:57:46 by mait-oub          #+#    #+#             */
/*   Updated: 2025/02/13 00:10:18 by mait-oub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static pid_t	retry_fork(unsigned int max_retries)
{
	pid_t			pid;
	unsigned int	seconds;

	seconds = 1;
	while (max_retries--)
	{
		pid = fork();
		if (pid != -1)
		{
			return (pid);
		}
		terminate("fork: retry", -1);
		xsleep(seconds);
		seconds <<= 1;
	}
	terminate("fork", -1);
	return (-1);
}

static int	setup_stdio(int *stdio)
{
	if (stdio[0] == -1 || dup2(stdio[0], STDIN_FILENO) == -1)
	{
		if (stdio[0] != -1)
		{
			terminate("dup2 failed", -1);
		}
		return (-1);
	}
	if (stdio[1] == -1 || dup2(stdio[1], STDOUT_FILENO) == -1)
	{
		if (stdio[1] != -1)
		{
			terminate("dup2 failed", -1);
		}
		if (close(STDIN_FILENO) == -1)
		{
			terminate("close failed", -1);
		}
		return (-1);
	}
	close_stdio(stdio);
	stdio[0] = STDIN_FILENO;
	stdio[1] = STDOUT_FILENO;
	return (0);
}

pid_t	create_child(t_child *child, int last_stdin)
{
	pid_t	pid;
	int		exit_status;

	pid = retry_fork(4);
	if (pid == -1)
	{
		return (-1);
	}
	if (pid == 0)
	{
		if (last_stdin != -1 && close(last_stdin) == -1)
		{
			terminate("close failed", -1);
		}
		exit_status = EXIT_FAILURE;
		if (setup_stdio(child->stdio) != -1)
		{
			exit_status = execute_child(child);
		}
		free_array(child->path);
		close_stdio(child->stdio);
		exit(exit_status);
	}
	return (pid);
}
