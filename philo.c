#include "philosophers.h"
typedef struct philosopher {
    int number_of_philosophers;
    time_t time_to_die;
    time_t time_to_eat;
    time_t time_to_sleep;
    size_t num_must_eat;
    pthread_mutex_t *forks;
    pthread_mutex_t print;
    pthread_mutex_t change;
    int status; 
    struct infos *philos;
} t_philosopher;

typedef struct infos {
    int Philo_index;
    pthread_t tid;
	time_t last_meal;
    int meals_eaten;
    time_t current_time;
    t_philosopher *pt;
} t_info;

time_t	ft_atoi_time_t(char *str)
{
	time_t		i;
	time_t		res;

	i = 0;
	res = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + str[i] - '0';
		if (res < 0)
			return (0);
		i++;
	}
	if (res == 0)
		return (0);
	return (res);
}
void assigning_values(int ac, char **argv, t_philosopher *philosopher)
{
    philosopher->number_of_philosophers = atoi(argv[1]); 
    philosopher->time_to_die = ft_atoi_time_t(argv[2]);
    philosopher->time_to_eat = ft_atoi_time_t(argv[3]);
    philosopher->time_to_sleep = ft_atoi_time_t(argv[4]);
    philosopher->num_must_eat = -1;
	philosopher->status = 1;
    if (ac == 6)
        philosopher->num_must_eat = atoi(argv[5]);
}

time_t getting_time(void)
{
    struct timeval time;
	time_t value;
    gettimeofday(&time, NULL);
	value = (time.tv_sec * 1000) + (time.tv_usec / 1000);
    return (value);
}
void initializing_mutexes(t_philosopher *philosopher)
{
    philosopher->forks = malloc(sizeof(pthread_mutex_t) * philosopher->number_of_philosophers);
    philosopher->philos = malloc(sizeof(t_info) * philosopher->number_of_philosophers);
    int i = 0;
    while (i < philosopher->number_of_philosophers)
    {
        pthread_mutex_init(&philosopher->forks[i], NULL);
        i++;
    }
    i = 0;
    while (i < philosopher->number_of_philosophers)
    {
        philosopher->philos[i].Philo_index = i + 1;
        //philosopher->philos[i].current_time = getting_time();
        philosopher->philos[i].meals_eaten = 0;
        philosopher->philos[i].pt = philosopher;
        i++;
    }  
    pthread_mutex_init(&philosopher->print, NULL);
    pthread_mutex_init(&philosopher->change, NULL);
}
void *executing_forks(void *philosopher)
{
    t_info *formated_philo = (t_info *) philosopher;
	
    while(1)
    {
        pthread_mutex_lock(&formated_philo->pt->forks[formated_philo->Philo_index - 1]);
        pthread_mutex_lock(&formated_philo->pt->forks[(formated_philo->Philo_index % formated_philo->pt->number_of_philosophers)]);
        pthread_mutex_lock(&formated_philo->pt->print);
        printf("%ld philo %d has taken fork\n", getting_time() - formated_philo->last_meal,formated_philo->Philo_index);
        printf("%ld philo %d has taken fork\n", getting_time() - formated_philo->last_meal,formated_philo->Philo_index);
        printf("%ld philo %d is eating\n", getting_time() - formated_philo->last_meal,formated_philo->Philo_index);
        pthread_mutex_lock(&formated_philo->pt->change);
		formated_philo->last_meal = getting_time();
		pthread_mutex_unlock(&formated_philo->pt->change);
		pthread_mutex_unlock(&formated_philo->pt->print);
        usleep(formated_philo->pt->time_to_eat * 1000);
        pthread_mutex_unlock(&formated_philo->pt->forks[formated_philo->Philo_index - 1]);
        pthread_mutex_unlock(&formated_philo->pt->forks[(formated_philo->Philo_index % formated_philo->pt->number_of_philosophers)]);
        pthread_mutex_lock(&formated_philo->pt->change);
        formated_philo->meals_eaten++;
        if (formated_philo->pt->num_must_eat != -1)
        {
            if (formated_philo->meals_eaten > formated_philo->pt->num_must_eat)
            {
                formated_philo->pt->status = ALIVE;
                pthread_mutex_unlock(&formated_philo->pt->change);
                return(NULL);
            }
        }
        pthread_mutex_unlock(&formated_philo->pt->change);
        pthread_mutex_lock(&formated_philo->pt->print);
        printf("%ld philo %d is sleeping\n",getting_time() - formated_philo->last_meal,formated_philo->Philo_index);
        pthread_mutex_unlock(&formated_philo->pt->print);
        usleep(formated_philo->pt->time_to_sleep * 1000);
        pthread_mutex_lock(&formated_philo->pt->print);
        printf("%ld philo %d is thinking\n", getting_time() - formated_philo->last_meal,formated_philo->Philo_index);
        pthread_mutex_unlock(&formated_philo->pt->print);
        usleep(100);
    }
    return 0;
}

void checking_death_and_meals(t_philosopher *philosopher)
{
	int i = 0;
    while (1)
    {
        pthread_mutex_lock(&philosopher->change);
		//printf("time : %ld \n", getting_time() - philosopher->philos[i].last_meal);
        if ((getting_time() - philosopher->philos[i].last_meal) > philosopher->time_to_die)
        {
            printf("%ld philo %d is dead\n",getting_time() - philosopher->philos[i].last_meal, philosopher->philos[i].Philo_index);
			philosopher->status = 0;
            //pthread_mutex_unlock(&philosopher->change);
            return;
        }
        pthread_mutex_unlock(&philosopher->change);
        usleep(1000); 
    }
}
void initializing_threads(t_philosopher *philosopher)
{
    int i = 0;
    while (i < philosopher->number_of_philosophers)
    {
		philosopher->philos[i].last_meal = getting_time();
		philosopher->philos[i].current_time = getting_time();
        pthread_create(&philosopher->philos[i].tid, NULL, &executing_forks, &philosopher->philos[i]);	
		//pthread_detach(philosopher->philos[i].tid);
        i++;
    }
	return ;
}
void ft_thread_join(t_philosopher *philosopher)
{
	int i = 0;
	while (i < philosopher ->number_of_philosophers && philosopher->status != 0)
	{
		pthread_join(philosopher->philos[i].tid, NULL);
        i++;
	}	
}
void destroying_mutexes(t_philosopher *philosopher)
{
	int i = 0;
	while (i < philosopher->number_of_philosophers)
	{
		pthread_mutex_destroy(&philosopher->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&philosopher->change);
	pthread_mutex_destroy(&philosopher->print);
}

int main(int argc, char **argv) 
{
    t_philosopher philosopher;
    if (argc < 5)
        return 0;
    assigning_values(argc, argv, &philosopher);
    initializing_mutexes(&philosopher);
    initializing_threads(&philosopher);
    checking_death_and_meals(&philosopher);
	ft_thread_join(&philosopher);
	destroying_mutexes(&philosopher);
    //usleep(300);
    return 0;
}
