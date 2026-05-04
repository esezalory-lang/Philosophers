/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3_routine_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esezalor <esezalor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 14:21:23 by esezalor          #+#    #+#             */
/*   Updated: 2026/05/04 10:32:44 by esezalor         ###   ########.fr       */
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
	precise_sleep(philo_p, philo_p->data->tte);
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
	long int	l_timestamp;
	int			l_mcount;

	present = get_mstime();
	pthread_mutex_lock(&philo->protect_meal);
	l_mcount = philo->meal_count;
	l_timestamp = philo->timestamp;
	pthread_mutex_unlock(&philo->protect_meal);
	if ((present - l_timestamp) > philo->data->ttd)
	{
		set_stop_flag(philo->data);
		return (print_state(philo, DIES), 1);
	}
	if (l_mcount >= philo->data->eat_cycle && (philo->data->eat_cycle != -1))
	{
		*full_philos += 1;
		if (*full_philos == philo->data->n_philo)
		{
			set_stop_flag(philo->data);
			return (print_state(philo, FULL), 1);
		}
	}
	return (0);
}

