/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souledla <souledla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 20:48:26 by souledla          #+#    #+#             */
/*   Updated: 2023/05/26 17:37:01 by souledla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

time_t	ft_atoi_time_t(char *str)
{
	time_t		i;
	time_t		resultat;

	i = 0;
	resultat = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		resultat = resultat * 10 + str[i] - '0';
		if (resultat < 0)
			return (0);
		i++;
	}
	return (resultat);
}

size_t	ft_atoi(char *str)
{
	int		i;
	size_t	resultat;

	i = 0;
	resultat = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		resultat = resultat * 10 + str[i] - '0';
		if (resultat < 0)
			return (0);
		i++;
	}
	return (resultat);
}
void	my_usleep(time_t mil_sec)
{
	time_t	current;
	// time_t	b_part;

	// b_part = mil_sec * 9 / 10;
	current = getting_time();
	// usleep(b_part * 1000);
	while (getting_time() - current < mil_sec)
		usleep(100);
}

time_t	getting_time(void)
{
	time_t			value;
	struct timeval	time;

	gettimeofday(&time, NULL);
	value = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	return (value);
}
