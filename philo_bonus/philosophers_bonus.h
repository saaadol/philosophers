/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_bonus.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souledla <souledla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 22:12:21 by souledla          #+#    #+#             */
/*   Updated: 2023/05/18 23:10:12 by souledla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_BONUS_H
# define PHILOSOPHERS_BONUS_H

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <unistd.h>
# include<sys/wait.h>
# include <semaphore.h>
# include <signal.h>

typedef struct philosopher
{
	int			number_of_philosophers;
	time_t		time_to_die;
	time_t		time_to_eat;
	time_t		time_to_sleep;
	time_t		time_start;
	int			num_must_eat;
	sem_t		*bonnie;
	sem_t		*clyde;
	struct info	*philos;
}	t_philosopher;

typedef struct info
{
	int				philo_index;
	int				meals_eaten;
	pid_t			philo_pid;
	pthread_t		tid;
	time_t			current_time;
	t_philosopher	*pt;
}	t_info;


void	*executing_routine(void *philosopher);
void	executing_task(t_philosopher *philosopher);
void	exiting_child_processes(t_philosopher *philosopher, int flag);
int		checking_values(int ac, char **av);
void	eating_routine_bonus(t_info *formated_philo);
void	sleeping_routine_bonus(t_info *formated_philo);
void	initializing_threads(t_info *philosopher);
void	thinking_routine_bonus(t_info *formated_philo);
time_t	ft_atoi_time_t(char *str);
int		ft_atoi(char *str);
time_t	getting_time(void);
void	sub_task(void *philosopher);
#endif