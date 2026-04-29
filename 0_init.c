/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0_init.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esezalor <esezalor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/27 18:14:38 by esezalor          #+#    #+#             */
/*   Updated: 2026/04/29 12:39:09 by esezalor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

// Shared Constant:
// - number_of_philosophers
// - time_to_die
// - time_to_eat
// - time_to_sleep

// Individual to each Philo
// - left fork
// - right fork
// - thread_id
// - philo_id
// - number of times it must eat
// - timestamp

static int	philo_init(t_philo **p_array, pthread_mutex_t **forks, int n_eats)
{
	int	i;
	int n;

	i = 0;
	n = p_array[0]->data->n_philo;
	while (i < n)
	{
		p_array[i] = ft_calloc(1, sizeof(t_philo));
		if (!p_array[i])
			return (1);
		p_array[i]->philo_id = i;
		p_array[i]->l_fork = &forks[i];
		p_array[i]->r_fork = &forks[(i + 1) % n];
		p_array[i]->eat_cycle = n_eats;
		p_array[i]->timestamp = n_eats;
		i++;
	}
	return (0);
}

static int	philo_mutex_alloc(t_philo **p_array, pthread_mutex_t **forks, int n)
{
	int	i;

	p_array = ft_calloc(n + 1, sizeof(t_philo *));
	if (!p_array)
		return (1);
	forks = ft_calloc(n + 1, sizeof(pthread_mutex_t));
	if (!forks)
		return (free(p_array), 1);
	while (i < n)
	{
		if (pthread_mutex_init(&forks[i], NULL) != 0)
			return (destroy_forks(forks, n), free(p_array), 1);
		i++;
	}
	return (0);
}

static void	data_init(char **argv, t_const *data)
{
	ft_bzero(&data, sizeof(t_const));
	data->n_philo = argv[1];
	data->ttd = argv[2];
	data->tte = argv[3];
	data->tts = argv[4];
}

int	philosophers(int argc, char **argv)
{
	t_const			data;
	t_philo			**p_array;
	pthread_mutex_t	**forks;
	int				i;

	if (argc != 6)
		return (printf("Wrong Number of Arguments\n"), 0);
	i = 0;
	data_init(argv, &data);
	if (philo_mutex_alloc(p_array, forks, data.n_philo))
		return (printf("Init Failure\n"), 0);
	if (philo_init(&data, p_array, argv[5]))
		return (free_philos(p_array, data.n_philo), destroy_forks(forks,
				data.n_philo), 0);
	destroy_forks(forks, data.n_philo);
	free_philos(p_array, data.n_philo);
}
