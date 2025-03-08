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

static char	*make_tempfile(const char *prefix, pid_t *zombie_pid)
{
	char	*tempfile;
	char	*uniq_pid;

	*zombie_pid = create_zombie();
	if (*zombie_pid == -1)
	{
		terminate("fork", -1);
		return (NULL);
	}
	uniq_pid = ft_itoa((int) *zombie_pid);
	tempfile = ft_strjoin(prefix, uniq_pid);
	if (uniq_pid == NULL || tempfile == NULL)
	{
		terminate("malloc", -1);
		waitpid(*zombie_pid, NULL, 0);
	}
	if (uniq_pid != NULL)
	{
		free(uniq_pid);
	}
	return (tempfile);
}

static int	create_tempfile(char **filepath, pid_t *zombie_pid)
{
	int		tempfile;

	*filepath = make_tempfile("/tmp/xsh-thd-", zombie_pid);
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

static int	raise_warning(const char *argv_0, char *delimiter)
{
	char	*warn_msg;

	warn_msg = ": warning: here-document delimited by end-of-file (wanted `";
	dprints(STDERR_FILENO, 5, "\n", argv_0, warn_msg, delimiter, "')\n");
	return (0);
}

static int	process_heredoc(const char *argv_0, int tempfile, char *delimiter)
{
	size_t	dlmtr_len;
	char	*line;

	dlmtr_len = ft_strlen(delimiter);
	while (1)
	{
		write(STDERR_FILENO, "> ", 2);
		line = get_next_line(STDIN_FILENO);
		if (line == NULL && errno == ENOMEM)
			return (terminate("malloc", -1));
		if (line == NULL)
			return (raise_warning(argv_0, delimiter));
		if (!ft_strncmp(line, delimiter, dlmtr_len) && line[dlmtr_len] == '\n')
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

int	heredoc(const char *argv_0, const char *delimiter)
{
	int		upstream;
	int		tempfile;
	char	*filepath;
	pid_t	zombie_pid;

	tempfile = create_tempfile(&filepath, &zombie_pid);
	if (tempfile != -1)
	{
		upstream = open(filepath, O_RDONLY);
		if (upstream == -1)
			terminate(filepath, -1);
		unlink(filepath);
		free(filepath);
		if (upstream != -1)
		{
			if (process_heredoc(argv_0, tempfile, (char *) delimiter) != -1)
			{
				return (close(tempfile), upstream);
			}
			close(upstream);
		}
		close(tempfile);
	}
	waitpid(zombie_pid, NULL, 0);
	return (-1);
}
