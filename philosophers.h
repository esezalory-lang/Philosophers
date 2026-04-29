/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esezalor <esezalor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/27 18:23:29 by esezalor          #+#    #+#             */
/*   Updated: 2026/04/29 12:23:06 by esezalor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILISOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>

typedef struct s_monitor
{
	int					is_alive;
}						t_monitor;

typedef struct s_constant
{
	int					n_philo;
	int					ttd;
	int					tte;
	int					tts;
}						t_const;

typedef struct s_philo
{
	struct s_constant	*data;
	pthread_mutex_t		*l_fork;
	pthread_mutex_t		*r_fork;
	pthread_t			thread_id;
	int					philo_id;
	int					eat_cycle;
	int					timestamp;

}						t_philo;

// 3. Utils
void					free_philos(t_philo **array, int n);
void					destroy_forks(pthread_mutex_t **forks, int n);

// 4. Libft Utils
void					ft_bzero(void *s, size_t n);
void					*ft_calloc(size_t nmemb, size_t size);
void					ft_putstr_fd(char *s, int fd);

#endif