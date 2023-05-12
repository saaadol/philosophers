#ifndef PHILOSOPHERS_BONUS_H
#define PHILOSOPHERS_BONUS_H

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>
#include <unistd.h>
#include<sys/wait.h>
#include <semaphore.h>

typedef struct philosopher
{
	int number_of_philosophers;
	time_t	time_to_die;
	time_t	time_to_eat;
	time_t	time_to_sleep;
	int		num_must_eat;
	t_info 	*philos;
	sem_t 	*forks;
} t_philosopher;

typedef struct info
{
	int Philo_index;
	int meals_eaten;
	pid_t philo_pid;
	pthread_t tid;
	time_t current_time;
	t_info *pt;
} t_info;
#endif