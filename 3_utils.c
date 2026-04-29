/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3_utils.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esezalor <esezalor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 10:55:19 by esezalor          #+#    #+#             */
/*   Updated: 2026/04/29 16:31:45 by esezalor         ###   ########.fr       */
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

void	destroy_forks(pthread_mutex_t *forks, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		pthread_mutex_destroy(&forks[i]);
		i++;
	}
	free(forks);
}

long int	get_mstime(void)
{
	long int		ms_time;
	struct timeval	current;

	if (gettimeofday(&current, NULL) != 0)
		return (-1);
	ms_time = (current.tv_sec * 1000) + (current.tv_usec / 1000);
	return (ms_time);
}
