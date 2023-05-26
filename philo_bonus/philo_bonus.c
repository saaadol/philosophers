/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souledla <souledla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 15:08:43 by souledla          #+#    #+#             */
/*   Updated: 2023/05/26 17:30:44 by souledla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

#include "philosophers_bonus.h"

void	*executing_routine(void *philosopher)
{	
	t_info	*formated_philo;

	formated_philo = (t_info *) philosopher;
	while (1)
	{
		sem_wait(formated_philo->pt->clyde);
		if (getting_time() - formated_philo->current_time
			>= formated_philo->pt->time_to_die)
		{
			sem_post(formated_philo->pt->clyde);
			sem_wait(formated_philo->pt->clyde);
			printf("%ld ms philo %d is dead\n", getting_time()
				- formated_philo->pt->time_start, formated_philo->philo_index);
			exit(1);
		}
		sem_post(formated_philo->pt->clyde);
		usleep(100);
	}
	return (NULL);
}

void	sub_task(void *philosopher)
{
	t_info	*formated_philo;

	formated_philo = (t_info *) philosopher;
	while (1)
	{
		eating_routine_bonus(formated_philo);
		sleeping_routine_bonus(formated_philo);
		thinking_routine_bonus(formated_philo);
		if (formated_philo->pt->num_must_eat != -1)
		{
			if (formated_philo->meals_eaten >= formated_philo->pt->num_must_eat)
			{
				exit(0);
			}
		}
	}
}

void	exiting_child_processes(t_philosopher *philosopher, int flag)
{
	// void    finish_simulation(t_data data, intf_pid, int id)

    int        i;
    int        stat;

    i = 0;
    if (flag == philosopher->number_of_philosophers)
        return ;
    waitpid(-1, &stat, 0);
    if (WIFEXITED(stat) && !WEXITSTATUS(stat))
	{
        return (exiting_child_processes(philosopher, flag + 1));
	}
    else
    {
        while (i < philosopher->number_of_philosophers)
        {
            kill(philosopher->philos[i].philo_pid, SIGKILL);
            i++;
        }

    }
    return ;
}

void	executing_task(t_philosopher *philosopher)
{
	int	i;
	int	flag = 0;

	i = 0;
	philosopher->time_start = getting_time();
	while (i < philosopher->number_of_philosophers)
	{	
		philosopher->philos[i].philo_pid = fork();
		if (philosopher->philos[i].philo_pid == 0)
		{
			// if (pthread_create(&philosopher->philos[i].tid, NULL,
			// 		&executing_routine, &philosopher->philos[i]) != 0)
			// 	exit(1);
			// if (pthread_detach(philosopher->philos[i].tid) != 0)
			// 	exit(1);
			
			sub_task(&philosopher->philos[i]);
			exit(1);
		}
		i++;
	}
	exiting_child_processes(philosopher, flag);
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
	initializing_values(philosopher);
	executing_task(philosopher);
	free(philosopher);
	return (0);
}