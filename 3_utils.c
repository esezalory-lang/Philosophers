/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3_utils.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esezalor <esezalor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 10:55:19 by esezalor          #+#    #+#             */
/*   Updated: 2026/04/29 12:23:06 by esezalor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	free_philos(t_philo **array, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		if (array[i])
			free(array[i]);
		i++;
	}
	free(array);
}

void	destroy_forks(pthread_mutex_t **forks, int n)
{
	int i;

	i = 0;
	while (i < n)
	{
		if (forks[i])
			pthread_mutex_destroy(&forks[i]);
		i++;
	}
	free(forks);
}