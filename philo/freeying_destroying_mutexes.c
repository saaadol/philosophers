/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freeying_destroying_mutexes.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souledla <souledla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 20:46:50 by souledla          #+#    #+#             */
/*   Updated: 2023/05/18 23:35:15 by souledla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	destroying_mutexes(t_philosopher *philosopher)
{
	size_t	i;

	i = 0;
	while (i < philosopher->number_of_philosophers)
	{
		pthread_mutex_destroy(&philosopher->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&philosopher->change);
	pthread_mutex_destroy(&philosopher->print);
}

void	freeing_memory(t_philosopher *philosopher)
{
	if (philosopher->forks)
		free(philosopher->forks);
	if (philosopher->philos)
		free(philosopher->philos);
}
