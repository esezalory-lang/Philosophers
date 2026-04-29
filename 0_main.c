/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0_main.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esezalor <esezalor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/27 18:14:38 by esezalor          #+#    #+#             */
/*   Updated: 2026/04/29 20:48:58 by esezalor         ###   ########.fr       */
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
	t_shared		data;
	t_philo			**p_array;
	pthread_mutex_t	*forks;
	int				i;

	if (argc < 5 || argc > 6)
		return (printf("Wrong Number of Arguments\n"), 0);
	i = 0;
	if(data_init(argv, &data))
		return(printf("Init Failure\n"), 0);
	p_array = ft_calloc(data.n_philo + 1, sizeof(t_philo *));
	if (!p_array)
		return (0);
	forks = ft_calloc(data.n_philo + 1, sizeof(pthread_mutex_t));
	if (!forks)
		return (free(p_array), 0);
	if (mutex_init(forks, data.n_philo))
		return (destroy_forks(&data, forks), free(p_array),
			printf("Init Failure\n"), 0);
	if (philo_init(&data, p_array, forks, argv))
		return (dismantling(&data, p_array, forks), 0);
	thread_ramp(p_array);
	dismantling(&data, p_array, forks);
	return (0);
}
