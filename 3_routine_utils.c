/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3_routine_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esezalor <esezalor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 14:21:23 by esezalor          #+#    #+#             */
/*   Updated: 2026/05/01 17:03:51 by esezalor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	mahlzeit(t_philo *philo_p)
{
	pthread_mutex_lock(&philo_p->protect_meal);
	philo_p->timestamp = get_mstime();
	philo_p->meal_count += 1;
	pthread_mutex_unlock(&philo_p->protect_meal);
	if (print_state(philo_p, EATS) == 1)
	{
		pthread_mutex_unlock(philo_p->r_fork);
		pthread_mutex_unlock(philo_p->l_fork);
		return (1);
	}
	if (stop_flag_check(philo_p) == 1)
	{
		pthread_mutex_unlock(philo_p->r_fork);
		pthread_mutex_unlock(philo_p->l_fork);
		return (1);
	}
	usleep(philo_p->data->tte * 1000);
	if (stop_flag_check(philo_p) == 1)
	{
		pthread_mutex_unlock(philo_p->r_fork);
		pthread_mutex_unlock(philo_p->l_fork);
		return (1);
	}
	return (pthread_mutex_unlock(philo_p->r_fork),
		pthread_mutex_unlock(philo_p->l_fork), 0);
}

int	taking_forks(t_philo *philo_p)
{
	if (philo_p->philo_id % 2 != 0)
	{
		pthread_mutex_lock(philo_p->r_fork);
		if (print_state(philo_p, FORKS) == 1)
			return (pthread_mutex_unlock(philo_p->r_fork), 1);
		pthread_mutex_lock(philo_p->l_fork);
		if (print_state(philo_p, FORKS) == 1)
			return (pthread_mutex_unlock(philo_p->l_fork),
				pthread_mutex_unlock(philo_p->r_fork), 1);
	}
	else
	{
		pthread_mutex_lock(philo_p->l_fork);
		if (print_state(philo_p, FORKS) == 1)
			return (pthread_mutex_unlock(philo_p->l_fork), 1);
		pthread_mutex_lock(philo_p->r_fork);
		if (print_state(philo_p, FORKS) == 1)
			return (pthread_mutex_unlock(philo_p->r_fork),
				pthread_mutex_unlock(philo_p->l_fork), 1);
	}
	return (0);
}

int	dead_or_full(t_philo *philo, int *full_philos)
{
	long int	present;

	pthread_mutex_lock(&philo->protect_meal);
	present = get_mstime();
	if ((present - philo->timestamp) > philo->data->ttd)
	{
		pthread_mutex_unlock(&philo->protect_meal);
		set_stop_flag(philo->data);
		return (print_state(philo, DIES), 1);
	}
	if (philo->meal_count >= philo->data->eat_cycle
		&& (philo->data->eat_cycle != -1))
	{
		*full_philos += 1;
		if (*full_philos == philo->data->n_philo)
		{
			pthread_mutex_unlock(&philo->protect_meal);
			set_stop_flag(philo->data);
			return (print_state(philo, DIES), 1);
		}
	}
	pthread_mutex_unlock(&philo->protect_meal);
	return (0);
}
