/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_functions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souledla <souledla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 21:19:16 by souledla          #+#    #+#             */
/*   Updated: 2023/05/26 17:37:44 by souledla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

void	eating_routine_bonus(t_info *formated_philo)
{
	sem_wait(formated_philo->pt->bonnie);
	sem_wait(formated_philo->pt->clyde);
	printf("%ld\t%d\thas taken a fork\n", getting_time()
		- formated_philo->pt->time_start, formated_philo->philo_index);
	sem_post(formated_philo->pt->clyde);
	sem_wait(formated_philo->pt->bonnie);
	sem_wait(formated_philo->pt->clyde);
	printf("%ld\t%d\thas taken a fork\n", getting_time()
		- formated_philo->pt->time_start, formated_philo->philo_index);
	sem_post(formated_philo->pt->clyde);
	sem_wait(formated_philo->pt->clyde);
	printf("%ld\t%d\tis eating\n", getting_time()
		- formated_philo->pt->time_start, formated_philo->philo_index);
	sem_post(formated_philo->pt->clyde);
	sem_wait(formated_philo->pt->clyde);
	formated_philo->current_time = getting_time();
	formated_philo->meals_eaten++;
	sem_post(formated_philo->pt->clyde);
	my_usleep(formated_philo->pt->time_to_eat);
	sem_post(formated_philo->pt->bonnie);
	sem_post(formated_philo->pt->bonnie);
}

void	sleeping_routine_bonus(t_info *formated_philo)
{
	sem_wait(formated_philo->pt->clyde);
	printf("%ld\t%d\tis sleeping\n", getting_time()
		- formated_philo->pt->time_start, formated_philo->philo_index);
	sem_post(formated_philo->pt->clyde);
	my_usleep(formated_philo->pt->time_to_sleep);
}

void	thinking_routine_bonus(t_info *formated_philo)
{
	sem_wait(formated_philo->pt->clyde);
	printf("%ld\t%d\tis thinking\n", getting_time()
		- formated_philo->pt->time_start, formated_philo->philo_index);
	sem_post(formated_philo->pt->clyde);
}
