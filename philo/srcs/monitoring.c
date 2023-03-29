/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgomes-d <mgomes-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 09:01:35 by mgomes-d          #+#    #+#             */
/*   Updated: 2023/03/29 11:02:22 by mgomes-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	eating_philo(t_data *data)
{
	int		i;
	int		last_meal;
	int		nb_philo;
	int		time_to_die;
	
	i = 0;
	pthread_mutex_lock(&data->lock_data);
	nb_philo = data->nb_philo;
	time_to_die = data->time_to_die;
	pthread_mutex_unlock(&data->lock_data);
	while (i < nb_philo)
	{
		ft_usleep(50);
		pthread_mutex_lock(&data->lock_data);
		last_meal = data->philo[i].time_last_meal;
		pthread_mutex_unlock(&data->lock_data);
		if ((get_time() >= time_to_die + last_meal))
		{
			//printf("get time %d \n time-to_die %d\nlast-meal%d\n", get_time(), time_to_die, last_meal);
			printf("%d %d died\n", get_time() - data->start_time, i + 1);
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

	i = 0;
	while (i < data->nb_philo)
	{
		pthread_mutex_lock(&data->lock_data);
		meals_time = data->philo[i].meals_time;
		pthread_mutex_unlock(&data->lock_data);
		if (meals_time >= data->nb_must_eat)
		{
			printf("%d %d died\n", get_time() - data->start_time, i + 1);
			pthread_mutex_lock(&data->lock_data);
			data->is_alive = 0;
			pthread_mutex_unlock(&data->lock_data);
			break ;
		}
		i++;
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
		//ft_usleep(50);
	}
	return (0);
}
