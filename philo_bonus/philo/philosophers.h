/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souledla <souledla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 20:51:12 by souledla          #+#    #+#             */
/*   Updated: 2023/05/18 20:51:12 by souledla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <unistd.h>
# include <sys/wait.h>

typedef struct philosopher {
	time_t			time_to_die;
	time_t			time_to_eat;
	time_t			time_to_sleep;
	time_t			time_print;
	size_t			number_of_philosophers;
	size_t			num_must_eat;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print;
	pthread_mutex_t	change;
	int				status;
	struct infos	*philos;
}	t_philosopher;

typedef struct infos {
	int				philo_index;
	pthread_t		tid;
	time_t			last_meal;
	int				meals_eaten;
	time_t			current_time;
	t_philosopher	*pt;
}	t_info;
void	*executing_forks(void *philosopher);
int		checking_death_and_meals(t_philosopher *philosopher);
int		initializing_threads(t_philosopher *philosopher);
int		ft_thread_join(t_philosopher *philosopher);
void	destroying_mutexes(t_philosopher *philosopher);
void	freeing_memory(t_philosopher *philosopher);
void	assigning_values(int ac, char **argv, t_philosopher *philosopher);
void	initializing_values(t_philosopher *philosopher);
int		initializing_mutexes(t_philosopher *philosopher);
int		checking_values(int ac, char **av);
void	eating_routine(t_info *formated_philo);
void	sleeping_routine(t_info *formated_philo);
void	thinking_routine(t_info *formated_philo);
time_t	ft_atoi_time_t(char *str);
size_t	ft_atoi(char *str);
time_t	getting_time(void);
#endif