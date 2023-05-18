/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine _functions.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souledla <souledla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 21:19:16 by souledla          #+#    #+#             */
/*   Updated: 2023/05/18 22:20:10 by souledla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

void	eating_routine_bonus(t_info *formated_philo)
{
	sem_wait(formated_philo->pt->bonnie);
	sem_wait(formated_philo->pt->clyde);
	printf("%ld ms philo %d has taken fork\n", getting_time()
		- formated_philo->pt->time_start, formated_philo->philo_index);
	sem_post(formated_philo->pt->clyde);
	sem_wait(formated_philo->pt->bonnie);
	sem_wait(formated_philo->pt->clyde);
	printf("%ld ms philo %d has taken fork\n", getting_time()
		- formated_philo->pt->time_start, formated_philo->philo_index);
	sem_post(formated_philo->pt->clyde);
	sem_wait(formated_philo->pt->clyde);
	printf("%ld ms philo %d is eating\n", getting_time()
		- formated_philo->pt->time_start, formated_philo->philo_index);
	sem_post(formated_philo->pt->clyde);
	sem_wait(formated_philo->pt->clyde);
	formated_philo->current_time = getting_time();
	sem_post(formated_philo->pt->clyde);
	formated_philo->meals_eaten++;
	usleep(formated_philo->pt->time_to_eat * 994);
	sem_post(formated_philo->pt->bonnie);
	sem_post(formated_philo->pt->bonnie);
}

void	sleeping_routine_bonus(t_info *formated_philo)
{
	sem_wait(formated_philo->pt->clyde);
	printf("%ld ms philo %d is sleeping\n", getting_time()
		- formated_philo->pt->time_start, formated_philo->philo_index);
	sem_post(formated_philo->pt->clyde);
	usleep(formated_philo->pt->time_to_sleep * 994);
}

void	thinking_routine_bonus(t_info *formated_philo)
{
	sem_wait(formated_philo->pt->clyde);
	printf("%ld ms philo %d is thinking\n", getting_time()
		- formated_philo->pt->time_start, formated_philo->philo_index);
	sem_post(formated_philo->pt->clyde);
}
