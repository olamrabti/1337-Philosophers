
#include "philo.h"

int get_eaten_meals(t_philo *philo)
{
    pthread_mutex_lock(&philo->dinner->check_meals_mtx);
    return philo->eaten_meals;
    pthread_mutex_unlock(&philo->dinner->check_meals_mtx);
}

void incr_eaten_meals(t_philo *philo)
{
    pthread_mutex_lock(&philo->dinner->check_meals_mtx);
    philo->eaten_meals++;
    pthread_mutex_unlock(&philo->dinner->check_meals_mtx);
}

int someone_is_dead(t_philo *philo)
{
    pthread_mutex_lock(&philo->dinner->is_dead_mtx);
    if (philo->dinner->dead_philo == 1)
    {
        pthread_mutex_unlock(&philo->dinner->is_dead_mtx);
        return 1;
    }
    pthread_mutex_unlock(&philo->dinner->is_dead_mtx);
    return 0;
}

void declare_someone_is_dead(t_dinner *dinner)
{
    pthread_mutex_lock(&dinner->is_dead_mtx);
    dinner->dead_philo = 1;
    pthread_mutex_unlock(&dinner->is_dead_mtx);
}

int philos_are_full(t_dinner *dinner)
{
    size_t i;

    i = 0;

    while (i < dinner->number_of_philos)
    {
        if (get_eaten_meals(&dinner->philos[i]) != dinner->eat_limit)
            return 1;
    }
    return 0;
}

void declare_philos_are_full(t_dinner *dinner)
{
    pthread_mutex_lock(&dinner->check_meals_mtx);
    dinner->all_full = 1;
    pthread_mutex_unlock(&dinner->check_meals_mtx);
}
