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
		terminate(NULL, 126);
	}
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
	size_t	idx;

	idx = 0;
	while (child->path[idx])
	{
		temp = pathjoin(child->path[idx++], argv[0]);
		if (temp == NULL)
			handle_exit(child, argv, *pathname);
		if (access(temp, F_OK) == 0)
		{
			if (access(temp, X_OK) == 0)
			{
				(free(*pathname), *pathname = temp);
				return ;
			}
			if (*pathname == NULL)
			{
				*pathname = ft_strdup(temp);
				if (*pathname == NULL)
					handle_exit(child, argv, temp);
			}
		}
		free(temp);
	}
}

static void	execute_from_path(t_child *child, char **argv)
{
	char	*pathname;
	char	*buff;

	pathname = NULL;
	get_pathname(child, argv, &pathname);
	free_array(child->path);
	if (pathname == NULL)
	{
		buff = ft_strjoin(argv[0], ": command not found\n");
		free_array(argv);
		close_stdio(child->stdio);
		if (buff == NULL)
			terminate(NULL, EXIT_FAILURE);
		write(2, buff, ft_strlen(buff));
		free(buff);
		terminate(NULL, 127);
	}
	if (execve(pathname, argv, child->envp) == -1)
	{
		free(pathname);
		free_array(argv);
		close_stdio(child->stdio);
		terminate(NULL, 126);
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
		write(2, ": command not found\n", 20);
		terminate(NULL, 127);
	}
	if (ft_strchr(argv[0], '/') == NULL)
		execute_from_path(child, argv);
	execute_absolute_path(child, argv);
}
