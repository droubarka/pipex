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

static int	execute(t_pipeline *pipeline, t_execute *execute)
{
	free_array(pipeline->splited_path);
	pipeline->splited_path = NULL;
	if (execve(execute->pathname, execute->argv, execute->envp) == -1)
	{
		terminate(execute->pathname, -1);
		return (126);
	}
	return (-1);
}

static char	*get_pathname(char **path, char *cmdname);
{
	char	*pathname;

	pathname = NULL;
	while (*path)
	{
		temp = pathjoin(*path, cmdname);
		if (temp == NULL)
		{
			terminate("malloc failed", -1);
			if (pathname != NULL)
			{
				free(pathname);
			}
			return (NULL);
		}
		if (access(temp, F_OK) == 0)
		{
			if (access(temp, X_OK) == 0)
			{
				if (pathname != NULL)
				{
					free(pathname);
				}
				return (temp);
			}
			if (pathname == NULL)
			{
				pathname = temp;
				temp = NULL;
			}
		}
		if (temp != NULL)
		{
			free(temp);
		}
		path++;
	}
	return (pathname);
}

static void	execute2(t_child *child, char **argv)
{
	char	*pathname;
	char	*buff;

	pathname = get_pathname(child->path, *argv);
	if (pathname == NULL && errno == ENOMEM)
	{
		terminate("malloc failed", -1);
		return (EXIT_FAILURE);
	}
	if (pathname == NULL)
	{
		buff = ft_strjoin(*argv, ": command not found\n");
		if (buff == NULL)
		{
			terminate("malloc failed", -1);
			return (EXIT_FAILURE);
		}
		write(2, buff, ft_strlen(buff));
		free(buff);
		return (127);
	}
	if (execute(pathname, argv, child->envp) != -1)
	{
		free(pathname);
		return (126);
	}
	return (0);
}

int	execute_child(t_pipeline *pipeline)
{
	t_execute	execute;
	t_child		*child;

	child = &pipeline->current_child;
	execute->argv = ft_split(child->cmdline, ' ');
	if (execute->argv == NULL)
	{
		terminate("malloc", -1);
		return (EXIT_FAILURE);
	}
	if (argv[0] == NULL)
	{
		write(2, ": command not found\n", 20);
		free_array(execute->argv);
		return (127);
	}
	execute->envp = child->envp;
	
	return ();
}

static execute_process()
{
	if (ft_strchr(argv[0], '/') != NULL)
	{
		execute->pathname = argv[0];
		exit_status = execute(execute);
	}
	else
	{
		exit_status = execute2(child, argv);
	}
	free_array(execute->argv);
	return (exit_status);
}
