/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-oub <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 09:20:39 by mait-oub          #+#    #+#             */
/*   Updated: 2025/01/16 09:20:40 by mait-oub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	int		exit_status;

	if (argc < 5)
	{
		errno = EINVAL;
		perror(argv[0]);
		exit(1);
	}
	exit_status = pipex(argc - 1, argv + 1, envp);
	return (exit_status);
}
