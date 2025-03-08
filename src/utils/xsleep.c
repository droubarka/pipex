/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xsleep.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-oub <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 00:00:56 by mait-oub          #+#    #+#             */
/*   Updated: 2025/03/08 03:43:46 by mait-oub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	xsleep(unsigned int seconds)
{
	int	counter;

	while (seconds--)
	{
		counter = 0;
		while (counter != -1)
		{
			counter++;
		}
	}
}
