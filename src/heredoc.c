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

static char	*make_tempfile(char *prefix)
{
	char	*pid;
	char	*tempfile;

	pid = ft_itoa((int) getpid());
	tempfile = ft_strjoin(prefix, pid);
	if (pid != NULL)
		free(pid);
	return (tempfile);
}

static int	create_tempfile(char **tempfile_path)
{
	int		tempfile;

	*tempfile_path = make_tempfile("/tmp/xsh-thd-");
	if (*tempfile_path == NULL)
		terminate("malloc failed", EXIT_FAILURE);
	tempfile = open(*tempfile_path, O_WRONLY | O_CREAT | O_TRUNC, 0600);
	if (tempfile == -1)
	{
		terminate(*tempfile_path, -1);
		free(*tempfile_path);
		*tempfile_path = make_tempfile(".xsh-thd-");
		if (*tempfile_path == NULL)
			terminate("malloc failed", EXIT_FAILURE);
		tempfile = open(*tempfile_path, O_WRONLY | O_CREAT | O_TRUNC, 0600);
		if (tempfile == -1)
		{
			terminate(*tempfile_path, -1);
			free(*tempfile_path);
			exit(EXIT_FAILURE);
		}
	}
	return (tempfile);
}

static int	raise_warning(char *argv_0, char *limiter)
{
	char	warning[WARN_MAX];
	char	*warn_msg;

	warn_msg = ": warning: here-document delimited by end-of-file (wanted `";
	*warning = '\0';
	ft_strlcat(warning, "\n", WARN_MAX);
	ft_strlcat(warning, argv_0, WARN_MAX);
	ft_strlcat(warning, warn_msg, WARN_MAX);
	ft_strlcat(warning, limiter, WARN_MAX);
	ft_strlcat(warning, "')\n", WARN_MAX);
	write(STDERR_FILENO, warning, ft_strlen(warning));
	return (0);
}

static int	process_heredoc(char *argv_0, int tempfile, char *limiter)
{
	size_t	lmtr_len;
	char	*line;

	lmtr_len = ft_strlen(limiter);
	while (1)
	{
		write(STDERR_FILENO, "> ", 2);
		line = get_next_line(STDIN_FILENO);
		if (line == NULL && errno == ENOMEM)
			return (terminate("malloc failed", -1));
		if (line == NULL)
			return (raise_warning(argv_0, limiter));
		if (!ft_strncmp(line, limiter, lmtr_len) && line[lmtr_len] == '\n')
		{
			free(line);
			return (0);
		}
		if (write(tempfile, line, ft_strlen(line)) == -1)
		{
			terminate("write failed", -1);
			free(line);
			return (-1);
		}
		free(line);
	}
}

int	heredoc(char *argv_0, char *limiter)
{
	int		upstream;
	int		tempfile;
	char	*tempfile_path;

	tempfile = create_tempfile(&tempfile_path);
	upstream = open(tempfile_path, O_RDONLY);
	if (upstream == -1)
	{
		terminate(tempfile_path, -1);
		unlink(tempfile_path);
		free(tempfile_path);
		close(tempfile);
		exit(EXIT_FAILURE);
	}
	unlink(tempfile_path);
	free(tempfile_path);
	if (process_heredoc(argv_0, tempfile, limiter) == -1)
	{
		close(tempfile);
		close(upstream);
		exit(EXIT_FAILURE);
	}
	close(tempfile);
	return (upstream);
}
