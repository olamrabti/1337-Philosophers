
#include "philo.h"

int get_eaten_meals(t_philo *philo)
{
    pthread_mutex_lock(&philo->simulation->check_meals_mtx);
    return philo->eaten_meals;
    pthread_mutex_unlock(&philo->simulation->check_meals_mtx);
}

void incr_eaten_meals(t_philo *philo)
{
    // pthread_mutex_lock(&philo->simulation->check_meals_mtx);
    // if (philo->simulation->eat_limit != -1)
    philo->eaten_meals++;
    // pthread_mutex_unlock(&philo->simulation->check_meals_mtx);
}

int someone_is_dead(t_philo *philo)
{
    pthread_mutex_lock(&philo->simulation->is_dead_mtx);
    if (philo->simulation->dead_philo == 1)
    {
        pthread_mutex_unlock(&philo->simulation->is_dead_mtx);
        return 1;
    }
    pthread_mutex_unlock(&philo->simulation->is_dead_mtx);
    return 0;
}

void declare_someone_is_dead(t_simulation *simulation)
{
    pthread_mutex_lock(&simulation->is_dead_mtx);
    simulation->dead_philo = 1;
    pthread_mutex_unlock(&simulation->is_dead_mtx);
}

int philos_are_full(t_simulation *simulation)
{
    size_t i;

    i = 0;
    while (i < simulation->number_of_philos)
    {
        if (simulation->philos[i].eaten_meals < simulation->eat_limit)
            return 1;
        i++;
    }
    return 0;
}

void declare_philos_are_full(t_simulation *simulation)
{
    pthread_mutex_lock(&simulation->full);
    simulation->all_full = 1;
    pthread_mutex_unlock(&simulation->full);
}
