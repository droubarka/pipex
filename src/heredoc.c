/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-oub <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 05:03:39 by mait-oub          #+#    #+#             */
/*   Updated: 2025/02/05 11:08:14 by mait-oub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static pid_t	create_zombie(void)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		exit(EXIT_SUCCESS);
	}
	return (pid);
}

static char	*make_tempfile(char *prefix)
{
	char	*tempfile;
	char	*uniq_pid;
	pid_t	zombie_pid;

	zombie_pid = create_zombie();
	if (zombie_pid == -1)
	{
		terminate("fork", -1);
		return (NULL);
	}
	uniq_pid = ft_itoa((int) zombie_pid);
	tempfile = ft_strjoin(prefix, uniq_pid);
	if (uniq_pid == NULL || tempfile == NULL)
	{
		terminate("malloc", -1);
		waitpid(zombie_pid, NULL, 0);
	}
	if (uniq_pid != NULL)
	{
		free(uniq_pid);
	}
	return (tempfile);
}

static int	create_tempfile(char **filepath)
{
	int		tempfile;

	*filepath = make_tempfile("/tmp/xsh-thd-");
	if (*filepath != NULL)
	{
		tempfile = open(*filepath, O_WRONLY | O_CREAT | O_TRUNC, 0600);
		if (tempfile != -1)
		{
			return (tempfile);
		}
		terminate(*filepath, -1);
		free(*filepath);
	}
	return (-1);
}

static int	raise_warning(char *argv_0, char *limiter)
{
	char	*warn_msg;

	warn_msg = ": warning: here-document delimited by end-of-file (wanted `";
	dprint(STDERR_FILENO, 5, "\n", argv_0, warn_msg, limiter, "')\n");
	return (0);
}

static int	process_heredoc(int tempfile, char *limiter)
{
	size_t	lmtr_len;
	char	*line;

	lmtr_len = ft_strlen(limiter);
	while (1)
	{
		write(STDERR_FILENO, "> ", 2);
		line = get_next_line(STDIN_FILENO);
		if (line == NULL && errno == ENOMEM)
			return (terminate("malloc", -1));
		if (line == NULL)
			return (raise_warning(limiter));
		if (!ft_strncmp(line, limiter, lmtr_len) && line[lmtr_len] == '\n')
		{
			free(line);
			return (0);
		}
		if (write(tempfile, line, ft_strlen(line)) == -1)
		{
			terminate("write", -1);
			free(line);
			return (-1);
		}
		free(line);
	}
}

int	heredoc(char *limiter)
{
	int		upstream;
	int		tempfile;
	char	*filepath;

	tempfile = create_tempfile(&filepath);
	if (tempfile != -1)
	{
		upstream = open(filepath, O_RDONLY);
		if (upstream == -1)
		{
			terminate(filepath, -1);
		}
		unlink(filepath);
		free(filepath);
		if (upstream != -1)
		{
			if (process_heredoc(tempfile, limiter) != -1)
			{
				close(tempfile);
				return (upstream);
			}
			close(upstream);
		}
		close(tempfile);
	}
	//? waitpid(zombie_pid, NULL, 0)
	return (-1);
}
