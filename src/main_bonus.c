/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
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
	int	heredoc_flag;
	int	upstream;

	heredoc_flag = 0;
	if (1 < argc)
		heredoc_flag = !ft_strncmp(argv[1], "here_doc", 9);
	if (argc < 5 || (heredoc_flag && argc < 6))
	{
		errno = EINVAL;
		perror(argv[0]);
		return (EXIT_FAILURE);
	}
	upstream = -1;
	if (heredoc_flag)
	{
		upstream = heredoc(argv[0], argv[2]);
		if (upstream == -1)
			return (EXIT_FAILURE);
		argv++;
		argc--;
	}
	terminate(argv[0], -2);
	exit_status = pipex(argc - 1, argv + 1, envp, upstream);
	return (exit_status);
}
