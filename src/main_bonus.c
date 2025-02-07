/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-oub <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 05:03:39 by mait-oub          #+#    #+#             */
/*   Updated: 2025/02/01 05:03:40 by mait-oub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	int	exit_status;
	int	upstream;

	if (argc < 5)
	{
		errno = EINVAL;
		perror(argv[0]);
		exit(EXIT_FAILURE);
	}
	terminate(argv[0], -2);

	upstream = -1;
	if (!ft_strncmp(argv[1], "here_doc", 9))
	{
		upstream = heredoc(argv[2]);
		argv += 2;
		argc -= 2;
	}

	exit_status = pipex(argc - 1, argv + 1, envp, upstream);
	return (exit_status);
}
