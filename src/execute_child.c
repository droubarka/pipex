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

static int	execute_cmd(t_execute *execute)
{
	if (execve(execute->pathname, execute->argv, execute->envp) == -1)
	{
		terminate(execute->pathname, -1);
		return (126);
	}
	return (-1);
}

static char	*get_pathname(char **path, char *cmdname)
{
	char	*pathname;
	char	*temp;

	pathname = NULL;
	while (*path)
	{
		temp = pathjoin(*path, cmdname);
		if (temp == NULL)
		{
			terminate("malloc", -1);
			return (free(pathname), NULL);
		}
		if (access(temp, F_OK) == 0)
		{
			if (access(temp, X_OK) == 0)
				return (free(pathname), temp);
			if (pathname == NULL)
			{
				pathname = temp;
				temp = NULL;
			}
		}
		free(temp);
		path++;
	}
	return (pathname);
}

static int	find_and_execute(t_pipeline *pipeline, t_execute *execute)
{
	execute->pathname = get_pathname(pipeline->splited_path, execute->argv[0]);
	if (execute->pathname == NULL && errno == ENOMEM)
	{
		terminate("malloc", -1);
		return (EXIT_FAILURE);
	}
	if (execute->pathname == NULL)
	{
		dprints(2, 2, execute->argv[0], ": command not found\n");
		return (127);
	}
	free(pipeline->splited_path);
	pipeline->splited_path = NULL;
	if (execute_cmd(execute) != -1)
	{
		free(execute->pathname);
		return (126);
	}
	return (EXIT_SUCCESS);
}

static int	setup_execute(t_child *child, t_execute *execute)
{
	execute->argv = ft_split(child->cmdline, ' ');
	if (execute->argv == NULL)
	{
		terminate("malloc", -1);
		return (EXIT_FAILURE);
	}
	if (execute->argv[0] == NULL)
	{
		write(2, ": command not found\n", 20);
		return (127);
	}
	execute->envp = child->envp;
	return (EXIT_SUCCESS);
}

int	execute_child(t_pipeline *pipeline)
{
	t_execute	execute;
	int			exit_status;

	exit_status = setup_execute(&pipeline->current_child, &execute);
	if (exit_status != EXIT_SUCCESS)
	{
		return (exit_status);
	}
	if (ft_strchr(execute.argv[0], '/') != NULL)
	{
		free(pipeline->splited_path);
		pipeline->splited_path = NULL;
		execute.pathname = execute.argv[0];
		exit_status = execute_cmd(&execute);
	}
	else
	{
		exit_status = find_and_execute(pipeline, &execute);
	}
	free_array(execute.argv);
	return (exit_status);
}
