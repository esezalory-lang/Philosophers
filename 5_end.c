/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   5_end.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esezalor <esezalor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 20:10:28 by esezalor          #+#    #+#             */
/*   Updated: 2026/04/29 20:27:11 by esezalor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void free_destroy_ramp(t_shared *data, t_philo **array, pthread_mutex_t *forks)
{
    free_philos(array, data->n_philo);
    destroy_mutex(data, forks);
}

void	free_philos(t_philo **array, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		if (array[i])
        {
			free(array[i]);
            pthread_mutex_destroy(&array[i]->protect_meal);
        }
		i++;
	}
	free(array);
}

void	destroy_mutex(t_shared *data, pthread_mutex_t *forks)
{
	int	i;

	i = 0;
	while (i < data->n_philo)
	{
		pthread_mutex_destroy(&forks[i]);
		i++;
	}
	free(forks);
	pthread_mutex_destroy(&data->stop_flag);
	pthread_mutex_destroy(&data->print);
}
