/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esezalor <esezalor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/27 18:23:29 by esezalor          #+#    #+#             */
/*   Updated: 2026/04/29 16:06:06 by esezalor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <limits.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

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
	long				timestamp;

}						t_philo;

// 1. Initialisation
void					data_init(char **argv, t_const *data);
int						mutex_init(pthread_mutex_t *forks, int n);
int						philo_init(t_const *data, t_philo **p_array,
							pthread_mutex_t *forks, char **argv);

// 2. Thread Init
int						thread_ramp(t_philo **p_array);
void					*start_routine(void *philo_p);

// 3. Utils
void					free_philos(t_philo **array, int n);
void					destroy_forks(pthread_mutex_t *forks, int n);

// 4. Libft Utils
int						ft_strlen(char *str);
void					ft_bzero(void *s, size_t n);
void					*ft_calloc(size_t nmemb, size_t size);
void					ft_putstr_fd(char *s, int fd);
long					ft_atoi(const char *nptr);

#endif