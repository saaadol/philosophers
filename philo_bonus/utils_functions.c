/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souledla <souledla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 21:20:10 by souledla          #+#    #+#             */
/*   Updated: 2023/05/26 17:37:13 by souledla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

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

int	ft_atoi(char *str)
{
	int		i;
	int		resultat;

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

time_t	getting_time(void)
{
	struct timeval	time;
	time_t			value;

	gettimeofday(&time, NULL);
	value = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	return (value);
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