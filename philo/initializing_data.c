/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializing_data.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souledla <souledla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 20:49:45 by souledla          #+#    #+#             */
/*   Updated: 2023/05/26 09:56:23 by souledla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	assigning_values(int ac, char **argv, t_philosopher *philosopher)
{
	philosopher->number_of_philosophers = ft_atoi(argv[1]);
	philosopher->time_to_die = ft_atoi_time_t(argv[2]);
	philosopher->time_to_eat = ft_atoi_time_t(argv[3]);
	philosopher->time_to_sleep = ft_atoi_time_t(argv[4]);
	philosopher->num_must_eat = -1;
	//philosopher->status = 1;
	if (ac == 6)
		philosopher->num_must_eat = ft_atoi(argv[5]);
}

void	initializing_values(t_philosopher *philosopher)
{
	size_t	i;

	i = 0;
	while (i < philosopher->number_of_philosophers)
	{
		philosopher->philos[i].philo_index = i + 1;
		philosopher->philos[i].meals_eaten = 0;
		philosopher->philos[i].pt = philosopher;
		philosopher->philos[i].last_meal = getting_time();
		i++;
	}
}

int	initializing_mutexes(t_philosopher *philosopher)
{
	size_t	i;

	philosopher->forks = malloc(sizeof(pthread_mutex_t)
			* philosopher->number_of_philosophers);
	philosopher->philos = malloc(sizeof(t_info)
			* philosopher->number_of_philosophers);
	philosopher->time_print = getting_time();
	if (!philosopher->forks || !philosopher->philos)
		return (0);
	i = 0;
	while (i < philosopher->number_of_philosophers)
	{
		if (pthread_mutex_init(&philosopher->forks[i], NULL) != 0)
			return (0);
		i++;
	}
	initializing_values(philosopher);
	if (pthread_mutex_init(&philosopher->print, NULL) != 0
		|| pthread_mutex_init(&philosopher->change, NULL) != 0)
		return (0);
	return (1);
}