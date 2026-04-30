/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esezalor <esezalor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/27 18:23:29 by esezalor          #+#    #+#             */
/*   Updated: 2026/04/30 17:49:30 by esezalor         ###   ########.fr       */
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

typedef struct s_shared
{
	int				n_philo;
	int				ttd;
	int				tte;
	int				tts;
	long int		start_time;
	int				eat_cycle;
	int				must_stop;
	pthread_mutex_t	stop_flag;
	pthread_mutex_t	print;
}					t_shared;

typedef struct s_philo
{
	struct s_shared	*data;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	protect_meal;
	pthread_t		thread_id;
	int				philo_id;
	int				meal_count;
	long int		timestamp;

}					t_philo;

// 1. Initialisation
int					data_init(char **argv, t_shared *data);
int					mutex_init(pthread_mutex_t *forks, int n);
int					philo_init(t_shared *data, t_philo **p_array,
						pthread_mutex_t *forks);

// 2. Routines
int					routines(t_philo **p_array);
void				*philo_routine(void *philo_p);
void				*monitor_routine(void *philo_array);

// 3. Routine Utils
int					mahlzeit(t_philo *philo_p);
int					taking_forks(t_philo *philo_p);
int					dead_or_full(t_philo *philo);

// 3. Dismantling Functions
void				dismantling(t_shared *data, t_philo **array,
						pthread_mutex_t *forks);
void				free_philos(t_philo **array, int n);
void				destroy_mutex(t_shared *data, pthread_mutex_t *forks);
int					born2die(t_philo **p_array, int n);

// 4. Utils
long int			get_mstime(void);
void				print_state(t_philo *philo_p, int i);
int					stop_flag_check(t_philo *philo_p);
int					set_stop_flag(t_philo *philo);

// 5. Libft Utils
int					ft_strlen(char *str);
void				ft_bzero(void *s, size_t n);
void				*ft_calloc(size_t nmemb, size_t size);
void				ft_putstr_fd(char *s, int fd);
long				ft_atoi(const char *nptr);

#endif