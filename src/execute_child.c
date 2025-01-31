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

static void	execute_absolute_path(t_child *child, char **argv)
{
	free_array(child->path);
	if (execve(argv[0], argv, child->envp) == -1)
	{
		free_array(argv);
		close_stdio(child->stdio);
		terminate(NULL, EXIT_FAILURE);
	}
}

static char	*pathjoin(char *path, char *filename)
{
	char	*pathname;
	char	*temp;

	pathname = ft_strjoin(path, "/");
	if (pathname != NULL)
	{
		temp = pathname;
		pathname = ft_strjoin(pathname, filename);
		free(temp);
	}
	return (pathname);
}

static void	handle_exit(t_child *child, char **argv, char *addr)
{
	free(addr);
	free_array(argv);
	free_array(child->path);
	close_stdio(child->stdio);
	terminate(NULL, EXIT_FAILURE);
}

static void	get_pathname(t_child *child, char **argv, char **pathname)
{
	char	*temp;

	while (*child->path)
	{
		temp = pathjoin(*child->path, argv[0]);
		if (temp == NULL)
			handle_exit(child, argv, *pathname);
		if (access(temp, F_OK))
		{
			if (access(temp, X_OK))
			{
				free(*pathname);
				*pathname = temp;
				break ;
			}
			if (*pathname == NULL)
			{
				*pathname = ft_strdup(temp);
				if (*pathname == NULL)
					handle_exit(child, argv, temp);
			}
		}
		free_array((char *[]){temp, *child->path++});
	}
}

static void	command_not_found(char *command)
{
	write(2, "", );
}

static void	execute_from_path(t_child *child, char **argv)
{
	char	*pathname;

	pathname = NULL;
	get_pathname(child, argv, &pathname);
	free_array(child->path);
	if (pathname == NULL)
	{
		command_not_found(argv[0]);
		free_array(argv);
		close_stdio(child->stdio);
		terminate(NULL, EXIT_FAILURE);
	}
	if (execve(pathname, argv, child->envp) == -1)
	{
		free(pathname);
		free_array(argv);
		close_stdio(child->stdio);
		terminate(NULL, EXIT_FAILURE);
	}
}

void	execute_child(t_child *child)
{
	char	**argv;

	argv = ft_split(child->cmdline, ' ');
	if (argv == NULL)
	{
		free_array(child->path);
		close_stdio(child->stdio);
		terminate(NULL, EXIT_FAILURE);
	}
	if (argv[0] == NULL)
	{
		free_array(argv);
		free_array(child->path);
		close_stdio(child->stdio);
		terminate("command '' not found", EXIT_FAILURE);
	}
	if (ft_strchr(argv[0], '/') == NULL)
		execute_from_path(child, argv);
	execute_absolute_path(child, argv);
}
