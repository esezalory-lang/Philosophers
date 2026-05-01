/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   5_utils.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esezalor <esezalor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 10:55:19 by esezalor          #+#    #+#             */
/*   Updated: 2026/04/30 18:55:21 by esezalor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long int	get_mstime(void)
{
	long int		ms_time;
	struct timeval	current;

	if (gettimeofday(&current, NULL) != 0)
		return (-1);
	ms_time = (current.tv_sec * 1000) + (current.tv_usec / 1000);
	return (ms_time);
}

int	print_state(t_philo *philo_p, int i)
{
	long int	elapsed_time;

	if (stop_flag_check(philo_p) == 1 && i != 0)
		return (1);
	pthread_mutex_lock(&philo_p->data->print);
	elapsed_time = get_mstime() - philo_p->data->start_time;
	if (i == FORKS)
		printf("%li %i has taken a fork\n", elapsed_time, philo_p->philo_id);
	else if (i == EATS)
		printf("%li %i is eating\n", elapsed_time, philo_p->philo_id);
	else if (i == SLEEPS)
		printf("%li %i is sleeping\n", elapsed_time, philo_p->philo_id);
	else if (i == THINKS)
		printf("%li %i is thinking\n", elapsed_time, philo_p->philo_id);
	else if (i == DIES)
		printf("%li %i died\n", elapsed_time, philo_p->philo_id);
	pthread_mutex_unlock(&philo_p->data->print);
	return (0);
}

int	stop_flag_check(t_philo *philo_p)
{
	pthread_mutex_lock(&philo_p->data->stop_flag);
	if (philo_p->data->must_stop == 1)
	{
		pthread_mutex_unlock(&philo_p->data->stop_flag);
		return (1);
	}
	pthread_mutex_unlock(&philo_p->data->stop_flag);
	return (0);
}

int	set_stop_flag(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->stop_flag);
	philo->data->must_stop = 1;
	pthread_mutex_unlock(&philo->data->stop_flag);
	print_state(philo, DIES);
	return (1);
}
