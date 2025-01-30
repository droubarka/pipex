/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-oub <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 21:08:24 by mait-oub          #+#    #+#             */
/*   Updated: 2025/01/29 21:09:25 by mait-oub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>

typedef struct s_child {
	int		rank;
	int		stdio[2];
	char	**path;
	char	**envp;
	char	*cmdline;
}	t_child;

void	terminate(char *s, int status);

int		setup_child_io(
			t_child *child, int n_childs, int *upstream, char **iofiles);
int		setup_child(t_child *child);
int		exec_child(t_child *child);

void	free_array(char **array);
void	close_stdio(int *stdio);

#endif
