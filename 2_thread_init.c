/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_thread_init.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esezalor <esezalor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 14:21:23 by esezalor          #+#    #+#             */
/*   Updated: 2026/04/29 15:04:39 by esezalor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*start_routine(void *philo_p)
{
	t_philo	*philo;

	philo = (t_philo *)philo_p;
	printf("Philo %i exists\n", philo->philo_id);
	return (NULL);
}

int	thread_ramp(t_philo **p_array)
{
	int i;
	int j;
	int n;

	n = p_array[0]->data->n_philo;
	i = 0;
	j = 0;
	while (i < n)
	{
		pthread_create(&p_array[i]->thread_id, NULL, start_routine, p_array[i]);
		i++;
	}
	while (j < n)
	{
		pthread_join(p_array[i]->thread_id, NULL);
		i++;
	}
}
