/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_functions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souledla <souledla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 20:44:30 by souledla          #+#    #+#             */
/*   Updated: 2023/05/26 10:43:15 by souledla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	eating_routine(t_info *formated_philo)
{
	pthread_mutex_lock(&formated_philo->pt
		->forks[formated_philo->philo_index - 1]);
			
	pthread_mutex_lock(&formated_philo->pt->print);
	
	printf("%ld philo %d has taken fork\n", getting_time()
		- formated_philo->pt->time_print, formated_philo->philo_index);
	pthread_mutex_unlock(&formated_philo->pt->print);
		
	pthread_mutex_lock(&formated_philo->pt
		->forks[formated_philo->philo_index
		% formated_philo->pt->number_of_philosophers]);
	pthread_mutex_lock(&formated_philo->pt->print);
	printf("%ld philo %d has taken fork\n", getting_time()
		- formated_philo->pt->time_print, formated_philo->philo_index);
	pthread_mutex_unlock(&formated_philo->pt->print);

	pthread_mutex_lock(&formated_philo->pt->print);
	printf("%ld philo %d is eating\n", getting_time()
		- formated_philo->pt->time_print, formated_philo->philo_index);
	pthread_mutex_unlock(&formated_philo->pt->print);
	
	pthread_mutex_lock(&formated_philo->pt->change);
	formated_philo->last_meal = getting_time();
	formated_philo->meals_eaten++;
	pthread_mutex_unlock(&formated_philo->pt->change);

	my_usleep(formated_philo->pt->time_to_eat);
	pthread_mutex_unlock(&formated_philo->pt
		->forks[formated_philo->philo_index - 1]);
	pthread_mutex_unlock(&formated_philo
		->pt->forks[formated_philo->philo_index
		% formated_philo->pt->number_of_philosophers]);
}

void	sleeping_routine(t_info *formated_philo)
{
	pthread_mutex_lock(&formated_philo->pt->print);
	printf("%ld philo %d is sleeping\n",getting_time()
		- formated_philo->pt->time_print, formated_philo->philo_index);
	pthread_mutex_unlock(&formated_philo->pt->print);
	my_usleep(formated_philo->pt->time_to_sleep );
}

void	thinking_routine(t_info *formated_philo)
{
	pthread_mutex_lock(&formated_philo->pt->print);
	printf("%ld philo %d is thinking\n", getting_time()
		- formated_philo->pt->time_print, formated_philo->philo_index);
	pthread_mutex_unlock(&formated_philo->pt->print);
}
