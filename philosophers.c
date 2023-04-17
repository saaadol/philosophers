#include "philosophers.h"
typedef struct philosophers
{
    int Philo_index;
    pthread_mutex_t left_fork_index;
    pthread_mutex_t right_fork_index;
    int time_of_last_meal ;
}   t_list;

void *executing_tasks(void *argument)
{
    t_list *philosopher = (t_list *) argument;
    while (1)
    {
        // Thinking
        printf("Philosopher %d is thinking\n", philosopher->Philo_index);
        
        // Picking up forks
        pthread_mutex_lock(&philosopher->left_fork_index);
        printf("Philosopher %d picked up left fork\n", philosopher->Philo_index);
        pthread_mutex_lock(&philosopher->right_fork_index);
        printf("Philosopher %d picked up right fork\n", philosopher->Philo_index);
        
        // Eating
        printf("Philoso pher %d is eating\n", philosopher->Philo_index);
        usleep(1000000); // simulate eating time
        
        // Releasing forks
        pthread_mutex_unlock(&philosopher->left_fork_index);
        printf("Philosopher %d released left fork\n", philosopher->Philo_index);
        pthread_mutex_unlock(&philosopher->right_fork_index);
        printf("Philosopher %d released right fork\n", philosopher->Philo_index);
        usleep(1000000);;
        // Sleeping
        printf("Philosopher %d is sleeping\n", philosopher->Philo_index);
        usleep(1000000); // simulate sleeping time
    };
    return NULL; 
    
}

void creating_threads(int number_of_philosophers, pthread_mutex_t *forks, t_list *philosophers)
{
    pthread_t   threads[number_of_philosophers];
    int         i = 0;
    while (i < number_of_philosophers)
    {
        if (i == number_of_philosophers - 1)
            philosophers[i].right_fork_index = &forks[0];
        else
            philosophers[i].right_fork_index = &forks[(i + 1) % number_of_philosophers];
        philosophers[i].Philo_index = i + 1;
        philosophers[i].left_fork_index = &forks[i];
        philosophers[i].right_fork_index = &forks[(i + 1) % number_of_philosophers];
        struct timeval current_time;
        gettimeofday(&current_time, NULL);
        philosophers[i].time_of_last_meal = current_time.tv_sec;
        pthread_mutex_init(&philosophers[i].left_fork_index, NULL);
        pthread_mutex_init(&philosophers[i].right_fork_index, NULL);
        i++;
    }
    i = 0;
    while (i < number_of_philosophers)
    {
        pthread_create(&threads[i], NULL, executing_tasks, &philosophers[i]);
        i++;
    }
    i = 0;
    while (i < number_of_philosophers)
        pthread_join(threads[i++], NULL);
}
int main(int argc, char *argv[])
{
    if (argc != 2) 
    {
        fprintf(stderr, "Usage: %s <number of philosophers>\n", argv[0]);
        return 1;
    }
    int num_philosophers = atoi(argv[1]);
    if (num_philosophers < 2) 
    {
        fprintf(stderr, "Number of philosophers must be at least 2\n");
        return 1;
    }
    pthread_mutex_t forks[num_philosophers];
    t_list philosophers[num_philosophers];
    for (int i = 0; i < num_philosophers; i++) {
        pthread_mutex_init(&forks[i], NULL);
    }
    creating_threads(num_philosophers, forks, philosophers);
    for (int i = 0; i < num_philosophers; i++) {
        pthread_mutex_destroy(&forks[i]);
    }
    return 0;
}