/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_routines.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esezalor <esezalor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 14:21:23 by esezalor          #+#    #+#             */
/*   Updated: 2026/04/30 17:27:30 by esezalor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*monitor_routine(void *philo_array)
{
	t_philo		**p_array;
	t_shared	*data;
	int			i;
	long int present;

	p_array = (t_philo **)philo_array;
	data = p_array[0]->data;
	while (1)
	{
		i = 0;
		while (i < data->n_philo)
		{
			pthread_mutex_lock(&p_array[i]->protect_meal);
			present = get_mstime();
			if((present - p_array[i]->timestamp) > data->ttd || p_array[i]->meal_count == data->eat_cycle)
			{
				dead_or_full(p_array[i]);
				return(NULL);
			}
			i++;
		}
	}
	return(NULL);
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
		if (taking_forks(philo) == 1)
			return (NULL);
		if (mahlzeit(philo) == 1)
			return (NULL);
		if (stop_flag_check(philo) == 1)
			return (NULL);
		print_state(philo, 3);
		usleep(philo->data->tts * 1000);
		if (stop_flag_check(philo) == 1)
			return (NULL);
		print_state(philo, 4);
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
