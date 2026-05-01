/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0_main.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esezalor <esezalor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/27 18:14:38 by esezalor          #+#    #+#             */
/*   Updated: 2026/05/01 15:36:51 by esezalor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <bits/pthreadtypes.h>

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

static int	just1_philo(t_shared *data)
{
	long int	elapsed_time;

	elapsed_time = get_mstime() - data->start_time;
	if (data->n_philo == 1)
	{
		printf("%li 0 has taken a fork\n", elapsed_time);
		usleep(data->ttd * 1000);
		elapsed_time = get_mstime() - data->start_time;
		printf("%li 0 died\n", elapsed_time);
		return (1);
	}
	return (0);
}

static int	argument_handling(int argc, char **argv)
{
	int	i;
	int	j;

	i = 1;
	if (argc < 5 || argc > 6)
		return (1);
	while (i < argc)
	{
		j = 0;
		while (argv[i][j])
		{
			if ((argv[i][j] >= 'a' && argv[i][j] <= 'z') || (argv[i][j] >= 'A'
					&& argv[i][j] <= 'Z'))
				return (1);
			j++;
		}
		if (ft_atoi(argv[i]) <= 0)
			return (1);
		i++;
	}
	return (0);
}

static int	main_init(int argc, char **argv, t_shared *data)
{
	if (argument_handling(argc, argv))
		return (printf("Arguments Error\n"), 1);
	if (data_init(argv, data))
		return (printf("Init Failure\n"), 1);
	return (0);
}

int	main(int argc, char **argv)
{
	t_shared		data;
	t_philo			**p_array;
	pthread_mutex_t	*forks;
	pthread_t		monitor;

	if (main_init(argc, argv, &data))
		return (0);
	p_array = ft_calloc(data.n_philo + 1, sizeof(t_philo *));
	if (!p_array)
		return (0);
	forks = ft_calloc(data.n_philo + 1, sizeof(pthread_mutex_t));
	if (!forks)
		return (free(p_array), 0);
	if (mutex_init(forks, data.n_philo))
		return (destroy_mutex(&data, forks), free(p_array),
			printf("Init Failure\n"), 0);
	if (philo_init(&data, p_array, forks))
		return (dismantling(&data, p_array, forks), 0);
	if (just1_philo(&data) == 1)
		return (dismantling(&data, p_array, forks), 0);
	routines(p_array, &monitor, 0);
	dismantling(&data, p_array, forks);
	return (0);
}
