/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-oub <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 23:02:08 by mait-oub          #+#    #+#             */
/*   Updated: 2024/10/27 23:02:10 by mait-oub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

static int	ft_abs(int n)
{
	if (n < 0)
	{
		return (-n);
	}
	return (n);
}

static int	countdigits(int n)
{
	int	size;

	size = 1;
	while (n / 10)
	{
		size++;
		n /= 10;
	}
	return (size);
}

static char	*alloc_a(int n, int size)
{
	int		idx;
	char	*a;

	a = malloc(sizeof(char) * size);
	if (a != NULL)
	{
		idx = size - 2;
		if (n < 0)
		{
			a[0] = '-';
		}
		if (n == 0)
		{
			a[0] = '0';
		}
		while (n)
		{
			a[idx--] = (char)(ft_abs(n % 10) + '0');
			n /= 10;
		}
		a[size - 1] = '\0';
	}
	return (a);
}

char	*ft_itoa(int n)
{
	int	size;

	size = 1;
	if (n < 0)
	{
		size += 1;
	}
	size += countdigits(n);
	return (alloc_a(n, size));
}
