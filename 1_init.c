/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_init.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esezalor <esezalor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 14:13:31 by esezalor          #+#    #+#             */
/*   Updated: 2026/04/29 16:11:57 by esezalor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	data_init(char **argv, t_const *data)
{
	ft_bzero(data, sizeof(t_const));
	data->n_philo = ft_atoi(argv[1]);
	data->ttd = ft_atoi(argv[2]);
	data->tte = ft_atoi(argv[3]);
	data->tts = ft_atoi(argv[4]);
}

int	mutex_init(pthread_mutex_t *forks, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		if (pthread_mutex_init(&forks[i], NULL) != 0)
			return (destroy_forks(forks, n), 1);
		i++;
	}
	return (0);
}

int	philo_init(t_const *data, t_philo **p_array, pthread_mutex_t *forks,
		char **argv)
{
	int				i;
	struct timeval	current;

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
		if (argv[5])
			p_array[i]->eat_cycle = ft_atoi(argv[5]);
		p_array[i]->timestamp = gettimeofday(&current, NULL);
		if (p_array[i]->timestamp == -1)
			return (1);
		i++;
	}
	return (0);
}
