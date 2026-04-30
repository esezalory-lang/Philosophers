/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3_routine_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esezalor <esezalor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 14:21:23 by esezalor          #+#    #+#             */
/*   Updated: 2026/04/30 17:28:34 by esezalor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	mahlzeit(t_philo *philo_p)
{
	pthread_mutex_lock(&philo_p->protect_meal);
	philo_p->timestamp = get_mstime();
	philo_p->meal_count += 1;
	pthread_mutex_unlock(&philo_p->protect_meal);
	if (stop_flag_check(philo_p) == 1)
		return (1);
	print_state(philo_p, 2);
	usleep(philo_p->data->tte * 1000);
	pthread_mutex_unlock(philo_p->r_fork);
	pthread_mutex_unlock(philo_p->l_fork);
	return (0);
}

int	taking_forks(t_philo *philo_p)
{
	if (philo_p->philo_id % 2 != 0)
	{
		pthread_mutex_lock(philo_p->r_fork);
		if (stop_flag_check(philo_p) == 1)
			return (pthread_mutex_unlock(philo_p->r_fork), 1);
		print_state(philo_p, 1);
		pthread_mutex_lock(philo_p->l_fork);
		if (stop_flag_check(philo_p) == 1)
			return (pthread_mutex_unlock(philo_p->l_fork),
				pthread_mutex_unlock(philo_p->r_fork), 1);
		print_state(philo_p, 1);
	}
	else
	{
		pthread_mutex_lock(philo_p->l_fork);
		if (stop_flag_check(philo_p) == 1)
			return (pthread_mutex_unlock(philo_p->l_fork), 1);
		print_state(philo_p, 1);
		pthread_mutex_lock(philo_p->r_fork);
		if (stop_flag_check(philo_p) == 1)
			return (pthread_mutex_unlock(philo_p->r_fork),
				pthread_mutex_unlock(philo_p->l_fork), 1);
		print_state(philo_p, 1);
	}
	return (0);
}

void	*dead_or_full(t_philo *philo)
{
	pthread_mutex_unlock(&philo->protect_meal);
	pthread_mutex_lock(&philo->data->stop_flag);
	philo->data->must_stop = 1;
	pthread_mutex_lock(&philo->data->stop_flag);
	if (stop_flag_check(philo) == 1)
		return (NULL);
	print_state(philo, 0);
	return (NULL);
}
