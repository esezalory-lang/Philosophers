/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_init.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esezalor <esezalor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 14:13:31 by esezalor          #+#    #+#             */
/*   Updated: 2026/04/29 21:01:08 by esezalor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	data_init(char **argv, t_shared *data)
{
	ft_bzero(data, sizeof(t_shared));
	data->n_philo = ft_atoi(argv[1]);
	data->ttd = ft_atoi(argv[2]);
	data->tte = ft_atoi(argv[3]);
	data->tts = ft_atoi(argv[4]);
	if(argv[5])
		data->eat_cycle = ft_atoi(argv[5]);
	else
		data->eat_cycle = -1;
	data->start_time = get_mstime();
	if(data->start_time == -1)
		return (1);
	pthread_mutex_init(&data->alive_flag, NULL);
	pthread_mutex_init(&data->print, NULL);
	return(0);
}

int	mutex_init(pthread_mutex_t *forks, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		if (pthread_mutex_init(&forks[i], NULL) != 0)
			return (1);
		i++;
	}
	return (0);
}

int	philo_init(t_shared *data, t_philo **p_array, pthread_mutex_t *forks)
{
	int	i;

	i = 0;
	while (i < data->n_philo)
	{
		p_array[i] = ft_calloc(1, sizeof(t_philo));
		if (!p_array[i])
			return (1);
		p_array[i]->data = data;
		p_array[i]->philo_id = i;
		p_array[i]->l_fork = &forks[i];
		p_array[i]->r_fork = &forks[(i + 1) % data->n_philo];
		p_array[i]->meal_count = 0;
		p_array[i]->timestamp = -1;
		pthread_mutex_init(&p_array[i]->protect_meal, NULL);
		i++;
	}
	return (0);
}
