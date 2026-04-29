/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0_main.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esezalor <esezalor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/27 18:14:38 by esezalor          #+#    #+#             */
/*   Updated: 2026/04/29 15:27:45 by esezalor         ###   ########.fr       */
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

int	main(int argc, char **argv)
{
	t_const			data;
	t_philo			**p_array;
	pthread_mutex_t	**forks;
	int				i;

	if (argc != 6)
		return (printf("Wrong Number of Arguments\n"), 0);
	i = 0;
	data_init(argv, &data);
	p_array = NULL;
	forks = NULL;
	if (philo_mutex_alloc(p_array, forks, data.n_philo))
		return (printf("Init Failure\n"), 0);
	if (philo_init(p_array, forks, argv[5]))
		return (free_philos(p_array, data.n_philo), destroy_forks(forks,
				data.n_philo), 0);
	thread_ramp(p_array);
	destroy_forks(forks, data.n_philo);
	free_philos(p_array, data.n_philo);
	return(0);
}
