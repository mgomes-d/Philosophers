/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgomes-d <mgomes-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 07:49:22 by mgomes-d          #+#    #+#             */
/*   Updated: 2023/03/26 19:21:18 by mgomes-d         ###   ########.fr       */
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

int	ft_atoi(const char *str);

typedef struct s_philo
{
	struct s_data	*data;
	int				philo_id;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
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
	struct timeval	test;
	t_philo			*philo;
	pthread_t		*philosophers;
	pthread_mutex_t	*fork;
}	t_data;

#endif
