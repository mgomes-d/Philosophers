/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgomes-d <mgomes-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 07:49:22 by mgomes-d          #+#    #+#             */
/*   Updated: 2023/03/28 11:17:51 by mgomes-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <limits.h>
# include <unistd.h>
# include <stdbool.h>
# include <sys/time.h>

# define MSG_EAT "is eating"
# define MSG_THINK "is thinking"
# define MSG_FORK "has taken a fork"
# define MSG_SLEEP "is sleeping"
# define MSG_DIE "died"

typedef struct s_philo
{
	struct s_data	*data;
	int				philo_id;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	int				time_last_meal;
	int				meals_time;
}	t_philo;

typedef struct s_data
{
	int				nb_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nb_must_eat;
	bool			is_alive;
	int				timestamp_ms;
	int				time;
	int				start_time;
	pthread_mutex_t	*time_mutex;
	t_philo			*philo;
	pthread_t		*philosophers;
	pthread_mutex_t	*fork;
	pthread_mutex_t	lock_data;
}	t_data;

int		ft_atoi(const char *str);
int		init_philo(t_data *data);
int		init_struct(t_data *data, char **av, int ac);
int		init_thread(t_data *data);
int		init_mutex(t_data *data);
void	*routine(void *philo_ptr);
int		error_exit(t_data *data);
int		get_time(t_philo *philo);

#endif
