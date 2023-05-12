#include "philosophers_bonus.h"

time_t getting_time(void)
{
    struct timeval time;
	time_t value;
    gettimeofday(&time, NULL);
	value = (time.tv_sec * 1000) + (time.tv_usec / 1000);
    return (value);
}

time_t	ft_atoi_time_t(char *str)
{
	time_t		i;
	time_t		resultat;

	i = 0;
	resultat = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		resultat = resultat * 10 + str[i] - '0';
		if (resultat < 0)
			return (0);
		i++;
	}
	return (resultat);
}
int	ft_atoi(char *str)
{
	int		i;
	int		resultat;

	i = 0;
	resultat = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		resultat = resultat * 10 + str[i] - '0';
		if (resultat < 0)
			return (0);
		i++;
	}
	return (resultat);
}


void assigning_values(int ac, char **av, t_philosopher *philosopher)
{
	philosopher->number_of_philosophers = ft_atoi(av[1]);
	philosopher->time_to_eat = ft_atoi(av[2]);
	philosopher->time_to_die =  ft_atoi_time_t(av[3]);
	philosopher->time_to_sleep =  ft_atoi_time_t(av[4]);
	philosopher->num_must_eat =  -1;
	if (ac == 6)
		philosopher->num_must_eat =  ft_atoi(av[5]);
	

}
void initilizing_values(t_philosopher *philosopher)
{

	int i = 0;
	philosopher->philos = malloc(sizeof(t_info) * philosopher->number_of_philosophers);
	sem_unlink("/Bonnie");
	sem_unlink("/Clyde");
	while (i < philosopher->number_of_philosophers)
	{
		philosopher->philos[i].Philo_index = i + 1;
		philosopher->philos[i].current_time = getting_time();
		philosopher->philos[i].meals_eaten = 0;
		philosopher->philos->pt = philosopher;
		i++;
	} 
	sem_open("/Bonnie", O_CREAT, 0644, philosopher->number_of_philosophers);
	sem_open("/Clyde", O_CREAT, 0644, 1);
}
void executing_routine(void *philosopher)
{
	t_info *philosopher = (t_info *) philosopher;
}
void initializing_threads(t_philosopher *philosopher)
{
	int i = 0;
	while (i < philosopher->number_of_philosophers)
	{
		pthread_create(philosopher->philos[i].tid, NULL, executing_routine, &philosopher->philos[i]);
		pthread_detach(philosopher->philos[i].tid);
		
		i++;
	}
	
}
void executing_task(t_philosopher *philosopher)
{
	int i = 0;
	while (i < philosopher->number_of_philosophers)
	{	
		philosopher->philos[i].philo_pid = fork();
		if (philosopher->philos[i].philo_pid == 0)
		{
			initializing_threads(&philosopher);
		}
	}
	

}
int main(int ac, char **av)
{
	t_philosopher *philosopher = malloc(sizeof(t_philosopher));
	assigning_values (ac, av, philosopher);
	initializing_values(philosopher);
	executing_task(philosopher);

	

}