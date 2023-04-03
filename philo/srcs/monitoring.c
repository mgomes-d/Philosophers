/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgomes-d <mgomes-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 09:01:35 by mgomes-d          #+#    #+#             */
/*   Updated: 2023/04/03 08:35:31 by mgomes-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	get_info(t_data *data, int *nb, int *time)
{
	pthread_mutex_lock(&data->lock_data);
	*nb = data->nb_philo;
	*time = data->time_to_die;
	pthread_mutex_unlock(&data->lock_data);
}

static int	eating_philo(t_data *data)
{
	int		i;
	int		last_meal;
	int		nb_philo;
	int		time_die;

	get_info(data, &nb_philo, &time_die);
	i = 0;
	while (i < nb_philo)
	{
		pthread_mutex_lock(&data->lock_data);
		last_meal = data->philo[i].time_last_meal;
		pthread_mutex_unlock(&data->lock_data);
		if ((get_time() >= time_die + last_meal))
		{
			show_msg(data->philo, MSG_DIE);
			pthread_mutex_lock(&data->lock_data);
			data->is_alive = 0;
			pthread_mutex_unlock(&data->lock_data);
			break ;
		}
		i++;
	}
	return (0);
}

static void	nb_check(t_data *data)
{
	int	i;
	int	meals_time;
	int	all_eat;

	i = 0;
	all_eat = 0;
	while (i < data->nb_philo)
	{
		pthread_mutex_lock(&data->lock_data);
		meals_time = data->philo[i].meals_time;
		pthread_mutex_unlock(&data->lock_data);
		if (meals_time >= data->nb_must_eat)
			all_eat++;
		i++;
	}
	if (all_eat == data->nb_philo)
	{
		pthread_mutex_lock(&data->lock_data);
		data->is_alive = 0;
		pthread_mutex_unlock(&data->lock_data);
	}
}

int	monitoring(t_data *data)
{
	int	is_alive;

	pthread_mutex_lock(&data->lock_data);
	is_alive = data->is_alive;
	pthread_mutex_unlock(&data->lock_data);
	while (is_alive)
	{
		eating_philo(data);
		if (data->nb_must_eat != -2)
			nb_check(data);
		pthread_mutex_lock(&data->lock_data);
		is_alive = data->is_alive;
		pthread_mutex_unlock(&data->lock_data);
	}
	return (0);
}
