/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_child.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-oub <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 09:57:46 by mait-oub          #+#    #+#             */
/*   Updated: 2025/01/22 09:57:52 by mait-oub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	execute_absolute_path(t_child *child, char **argv)
{
	free_array(child->path);
	child->path = NULL;
	if (execve(argv[0], argv, child->envp) == -1)
	{
		terminate(argv[0], -1);
		return (126);
	}
	return (-1);
}

static int	check_access(char **filepath, char **resolved_path)
{
	if (access(*filepath, F_OK) == 0)
	{
		if (access(*filepath, X_OK) == 0)
		{
			if (*resolved_path != NULL)
			{
				free(*resolved_path);
			}
			*resolved_path = *filepath;
			return (0);
		}
		if (*resolved_path == NULL)
		{
			*resolved_path = *filepath;
			*filepath = NULL;
		}
	}
	if (*filepath != NULL)
	{
		free(*filepath);
		filepath = NULL;
	}
	return (-1);
}

static int	get_pathname(t_child *child, char **argv, char **pathname)
{
	char	*temp;
	size_t	idx;

	idx = 0;
	*pathname = NULL;
	while (child->path[idx])
	{
		temp = pathjoin(child->path[idx++], argv[0]);
		if (temp == NULL)
		{
			terminate("malloc failed", -1);
			if (pathname != NULL)
				free(pathname);
			return (-1);
		}
		if (check_access(&temp, pathname) != -1)
		{
			return (0);
		}
	}
	return (0);
}

static int	execute_from_path(t_child *child, char **argv)
{
	char	*pathname;
	char	*buff;

	if (get_pathname(child, argv, &pathname) == -1)
		return (EXIT_FAILURE);
	free_array(child->path);
	child->path = NULL;
	if (pathname == NULL)
	{
		buff = ft_strjoin(argv[0], ": command not found\n");
		if (buff == NULL)
		{
			terminate("malloc failed", -1);
			return (EXIT_FAILURE);
		}
		write(2, buff, ft_strlen(buff));
		free(buff);
		return (127);
	}
	if (execve(pathname, argv, child->envp) == -1)
	{
		terminate(pathname, -1);
		free(pathname);
		return (126);
	}
	return (0);
}

int	execute_child(t_child *child)
{
	char	**argv;
	int		exit_status;

	argv = ft_split(child->cmdline, ' ');
	if (argv == NULL)
	{
		terminate("malloc failed", -1);
		return (EXIT_FAILURE);
	}
	if (argv[0] == NULL)
	{
		write(2, ": command not found\n", 20);
		free_array(argv);
		return (127);
	}
	if (ft_strchr(argv[0], '/') != NULL)
	{
		exit_status = execute_absolute_path(child, argv);
	}
	else
	{
		exit_status = execute_from_path(child, argv);
	}
	free_array(argv);
	return (exit_status);
}
