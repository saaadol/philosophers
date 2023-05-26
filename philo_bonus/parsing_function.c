/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_function.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souledla <souledla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 21:25:26 by souledla          #+#    #+#             */
/*   Updated: 2023/05/18 23:44:48 by souledla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

int	checking_values(int ac, char **av)
{
	int	x;
	int	y;

	(void) ac;
	x = 1;
	while (av[x])
	{
		y = 0;
		while (av[x][y])
		{
			if (av[x][y] < '0' || av[x][y] > '9')
			{
				write(2, "ERROR\n", 6);
				return (0);
			}
			y++;
		}
		x++;
	}
	return (1);
}
