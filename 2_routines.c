/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_routines.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esezalor <esezalor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 14:21:23 by esezalor          #+#    #+#             */
/*   Updated: 2026/05/01 10:29:30 by esezalor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*monitor_routine(void *philo_array)
{
	t_philo		**p_array;
	t_shared	*data;
	int			i;
	int			full_philos;

	p_array = (t_philo **)philo_array;
	data = p_array[0]->data;
	while (1)
	{
		i = 0;
		full_philos = 0;
		while (i < data->n_philo)
		{
			if (dead_or_full(p_array[i], &full_philos) == 1)
				return (NULL);
			i++;
		}
		usleep(1000);
	}
	return (NULL);
}

void	*philo_routine(void *philo_p)
{
	t_philo	*philo;

	philo = (t_philo *)philo_p;
	if (stop_flag_check(philo) == 1)
		return (NULL);
	if (philo->philo_id % 2 != 0)
		usleep(100);
	while (stop_flag_check(philo) != 1)
	{
		if (taking_forks(philo) == 1 || mahlzeit(philo) == 1)
			return (NULL);
		if (print_state(philo, SLEEPS) == 1)
			return (NULL);
		if (stop_flag_check(philo) == 1)
			return (NULL);
		usleep(philo->data->tts * 1000);
		if (print_state(philo, THINKS) == 1)
			return (NULL);
	}
	return (NULL);
}

int	routines(t_philo **p_array)
{
	t_shared	*data;
	pthread_t	monitor;
	int			i;
	int			k;

	data = p_array[0]->data;
	i = 0;
	k = 0;
	while (i < data->n_philo)
	{
		if (pthread_create(&p_array[i]->thread_id, NULL, philo_routine,
				p_array[i]) != 0)
			return (born2die(p_array, i));
		i++;
	}
	if (pthread_create(&monitor, NULL, monitor_routine, p_array) != 0)
		return (born2die(p_array, i));
	while (k < data->n_philo)
	{
		pthread_join(p_array[k]->thread_id, NULL);
		k++;
	}
	pthread_join(monitor, NULL);
	return (0);
}
