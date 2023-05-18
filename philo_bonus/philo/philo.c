/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souledla <souledla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 19:29:25 by souledla          #+#    #+#             */
/*   Updated: 2023/05/16 19:29:25 by souledla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*executing_forks(void *philosopher)
{
	t_info	*formated_philo;

	formated_philo = (t_info *) philosopher;
	while (1)
	{
		eating_routine(formated_philo);
		pthread_mutex_lock(&formated_philo->pt->change);
		formated_philo->meals_eaten++;
		if (formated_philo->pt->num_must_eat != -1)
		{
			if (formated_philo->meals_eaten > formated_philo->pt->num_must_eat)
			{
				formated_philo->pt->status = 0;
				pthread_mutex_unlock(&formated_philo->pt->change);
				return (NULL);
			}
		}
		pthread_mutex_unlock(&formated_philo->pt->change);
		sleeping_routine(formated_philo);
		thinking_routine(formated_philo);
		usleep(100);
	}
	return (0);
}

int	checking_death_and_meals(t_philosopher *philosopher)
{
	int	i;

	i = 0;
	while (1)
	{
		if (pthread_mutex_lock(&philosopher->change) != 0)
			return (0);
		if ((getting_time() - philosopher->philos[i].last_meal)
			> philosopher->time_to_die)
		{
			if (pthread_mutex_lock(&philosopher->print) != 0)
				return (0);
			printf("%ld philo %d is dead\n", getting_time()
				- philosopher->philos[i].last_meal,
				philosopher->philos[i].philo_index);
			philosopher->status = 0;
			return (1);
		}
		if (pthread_mutex_unlock(&philosopher->change) != 0)
			return (0);
		usleep(1000);
	}
	return (1);
}

int	initializing_threads(t_philosopher *philosopher)
{
	int	i;

	i = 0;
	while (i < philosopher->number_of_philosophers)
	{
		if (pthread_create(&philosopher->philos[i].tid, NULL,
				&executing_forks, &philosopher->philos[i]) != 0)
			return (1);
		i++;
	}
	return (0);
}

int	ft_thread_join(t_philosopher *philosopher)
{
	int	i;

	i = 0;
	while (i < philosopher ->number_of_philosophers && philosopher->status != 0)
	{
		if (pthread_join(philosopher->philos[i].tid, NULL) != 0)
			return (0);
		i++;
	}
	return (1);
}

int	main(int ac, char **av)
{
	t_philosopher	*philosopher;

	if (ac < 5)
		return (0);
	if (checking_values(ac, av) == 0)
		return (0);
	philosopher = malloc(sizeof(t_philosopher));
	if (!philosopher)
		return (0);
	assigning_values(ac, av, philosopher);
	if (initializing_mutexes(philosopher) == 0
		|| initializing_threads(philosopher) == 1
		|| checking_death_and_meals(philosopher) == 0
		|| ft_thread_join(philosopher) == 0)
	{
		destroying_mutexes(philosopher);
		freeing_memory(philosopher);
		return (0);
	}	
	destroying_mutexes(philosopher);
	freeing_memory(philosopher);
	free(philosopher);
	return (0);
}
