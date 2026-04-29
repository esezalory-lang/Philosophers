/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esezalor <esezalor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/27 18:23:29 by esezalor          #+#    #+#             */
/*   Updated: 2026/04/29 20:18:19 by esezalor         ###   ########.fr       */
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
	int				is_alive;
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
void				data_init(char **argv, t_shared *data);
int					mutex_init(pthread_mutex_t *forks, int n);
int					philo_init(t_shared *data, t_philo **p_array,
						pthread_mutex_t *forks, char **argv);

// 2. Thread Init
int					thread_ramp(t_philo **p_array);
void				*start_routine(void *philo_p);

// 3. Utils
long int			get_mstime(void);

// 4. Libft Utils
int					ft_strlen(char *str);
void				ft_bzero(void *s, size_t n);
void				*ft_calloc(size_t nmemb, size_t size);
void				ft_putstr_fd(char *s, int fd);
long				ft_atoi(const char *nptr);

// 5. End Functions
void free_destroy_ramp(t_shared *data, t_philo **array, pthread_mutex_t *forks);
void				free_philos(t_philo **array, int n);
void				destroy_mutex(t_shared *data, pthread_mutex_t *forks);

#endif