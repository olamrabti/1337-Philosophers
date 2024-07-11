
#include "philo.h"

// TODO change file name to more segnificant one 

void incr_eaten_meals(t_philo *philo)
{
    pthread_mutex_lock(&philo->simulation->check_meals_mtx);
    philo->eaten_meals++;
    pthread_mutex_unlock(&philo->simulation->check_meals_mtx);
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

int raised_flags(t_philo *philo)
{
    if (ft_all_full(philo))
        return 1;
    pthread_mutex_lock(&philo->simulation->is_dead_mtx);
    if (philo->simulation->dead_philo)
        return pthread_mutex_unlock(&philo->simulation->is_dead_mtx), 1;
    pthread_mutex_unlock(&philo->simulation->is_dead_mtx);
    return 0;
}

int philos_are_full(t_simulation *simulation)
{
    size_t i;
    int temp_el;

    temp_el = simulation->eat_limit;

    i = 0;
    while (i < simulation->number_of_philos)
    {
        pthread_mutex_lock(&simulation->check_meals_mtx);
        if (simulation->philos[i].eaten_meals < temp_el)
            return pthread_mutex_unlock(&simulation->check_meals_mtx), 1;
        pthread_mutex_unlock(&simulation->check_meals_mtx);
        i++;
    }
    return 0;
}

void declare_philos_are_full(t_simulation *simulation)
{
    pthread_mutex_lock(&simulation->full);
    pthread_mutex_lock(&simulation->print_mtx);
    simulation->all_full = 1;
    pthread_mutex_unlock(&simulation->full);
}
