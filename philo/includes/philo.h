/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgomes-d <mgomes-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 07:49:22 by mgomes-d          #+#    #+#             */
/*   Updated: 2023/04/03 09:03:50 by mgomes-d         ###   ########.fr       */
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
# define MSG_ARG "Error : invalid arguments\n"
# define MSG_MUTEX "Error : mutex failed\n"
# define MSG_MALLOC "Error : malloc failed\n"
# define MSG_THREAD "Error : thread failed\n"

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
	t_philo			*philo;
	pthread_t		*philosophers;
	pthread_mutex_t	*fork;
	pthread_mutex_t	lock_data;
}	t_data;

/*init*/
int		init_philo(t_data *data);
int		init_struct(t_data *data, char **av, int ac);
int		init_thread(t_data *data);
int		init_mutex(t_data *data);
/*monitoring*/
int		monitoring(t_data *data);
/*routine*/
void	*routine(void *philo_ptr);
/*parsing*/
int		ft_check_args(char **av);
int		struct_check(t_data *data);
/*error*/
void	free_everthing(t_data *data);
int		error_exit(t_data *data, char *msg, int i, int size);
/*utils*/
int		ft_atoi(const char *str);
int		get_time_philo(t_philo *philo);
int		get_time(void);
void	ft_usleep(int ms);
void	show_msg(t_philo *philo, char *msg);
/*utils_2*/
int		join_threads(t_data *data, int size);
int		destroy_mutex(t_data *data, int size);

#endif
