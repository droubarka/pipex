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

static int	get_user_lines(int tempfile, char *limiter)
{
	size_t	lmtr_len;
	char	*line;

	lmtr_len = ft_strlen(limiter);
	while (1)
	{
		write(2, "heredoc> ", 9); //?
		line = get_next_line(STDIN_FILENO);
		if (line == NULL && errno == ENOMEM)
		{
			terminate("malloc failed", -1);
			close(tempfile);
			return (-1);
		}
		if (line == NULL) //?
		{
			terminate("warning: here-document at line %n delimited by end-of-file (wanted `%eof')", -1);
			close(tempfile);
			return (0);
		}
		if (!ft_strncmp(line, limiter, lmtr_len) && line[lmtr_len] == '\n')
		{
			free(line);
			close(tempfile);
			return (0);
		}
		write(tempfile, line, ft_strlen(line)); //?
		free(line);
	}
	return (0);
}

int	heredoc(char *limiter)
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
	// tempfile: open
	if (fn() == -1)
	{
		close(upstream);
		return (-1);
	}
	return (0);
}

/*
HEREDOC PROMPT: (PTS2)
	- The prompt itself is not part of the heredoc content. It is just a visual indicator.
	- The heredoc prompt (e.g., >) is displayed by the shell to indicate that it is waiting
	  for heredoc input.
*/
