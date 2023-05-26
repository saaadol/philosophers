/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializing_data.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souledla <souledla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 21:22:33 by souledla          #+#    #+#             */
/*   Updated: 2023/05/26 16:58:51 by souledla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

void	assigning_values(int ac, char **av, t_philosopher *philosopher)
{
	philosopher->number_of_philosophers = ft_atoi(av[1]);
	philosopher->time_to_die = ft_atoi(av[2]);
	philosopher->time_to_eat = ft_atoi_time_t(av[3]);
	philosopher->time_to_sleep = ft_atoi_time_t(av[4]);
	philosopher->num_must_eat = -1;
	if (ac == 6)
		philosopher->num_must_eat = ft_atoi(av[5]);
}

void	initializing_values(t_philosopher *philosopher)
{
	int	i;

	i = 0;
	philosopher->philos = malloc(sizeof(t_info)
			* philosopher->number_of_philosophers);
	if (!philosopher->philos)
		exit(1);
	sem_unlink("/bonnie");
	sem_unlink("/clyde");
	while (i < philosopher->number_of_philosophers)
	{
		philosopher->philos[i].philo_index = i + 1 ;
		philosopher->philos[i].current_time = getting_time();
		philosopher->philos[i].meals_eaten = 0;
		philosopher->philos[i].pt = philosopher;
		i++;
	}
	philosopher->bonnie = sem_open("/bonnie", O_CREAT, 0644,
			philosopher->number_of_philosophers);
	philosopher->clyde = sem_open("/clyde", O_CREAT, 0644, 1);
	if (!philosopher->bonnie || !philosopher->clyde)
		exit(1);
}