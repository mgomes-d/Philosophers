/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgomes-d <mgomes-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 07:39:01 by mgomes-d          #+#    #+#             */
/*   Updated: 2023/03/27 11:03:24 by mgomes-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_philo(t_data *data)
{
	int	i;

	i = 0;
	data->philo = malloc(sizeof(t_philo) * data->nb_philo);
	if (!data->philo)
		return (error_exit(data));
	while (i < data->nb_philo)
	{
		data->philo[i].philo_id = i + 1;
		data->philo[i].data = data;
		if (i == 0)
		{
			data->philo[i].left_fork = &data->fork[data->nb_philo - 1];
			data->philo[i].right_fork = &data->fork[i];	
		}
		else
		{
			data->philo[i].left_fork = &data->fork[i];
			data->philo[i].right_fork = &data->fork[i + 1];
		}
		i++;
	}
	return (0);
}

int	init_struct(t_data *data, char **av, int ac)
{
	struct timeval	time;

	data->nb_philo = ft_atoi(av[1]);
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		data->nb_must_eat = ft_atoi(av[5]);
	else
		data->nb_must_eat = -1;
	if ((gettimeofday(&time, 0)) == -1)
		return (1);
	data->start_time = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	data->is_alive = 1;
	if (init_mutex(data))
		return (1);
	if (init_philo(data))
		return (1);
	if (init_thread(data))
		return (1);
	return (0);
}

int	monitoring(t_data *data)
{
	int	now_time;
	int	last_time;
	int	result;
	int	i;

	i = 0;
	while (i++ < 10)
	{
		last_time = data->philo[i].time_last_meal;
		now_time = get_time(data->philo[i]);
		pthread_mutex_lock(&data->lock_data);
		result = (now_time - last_time) - data->time_to_die;
		pthread_mutex_unlock(&data->lock_data);
		if (result > 0)
			break;
	}
}

int	init_thread(t_data *data)
{
	int	i;

	i = 0;
	data->philosophers = malloc(sizeof(pthread_t) * data->nb_philo);
	if (!data->philosophers)
		return (error_exit(data));
	while (i < data->nb_philo)
	{
		if (pthread_create(&data->philosophers[i], NULL, &routine, &data->philo[i]) != 0)
			return (error_exit(data));
		usleep(1000);
		i++;
	}
	monitoring(data);
	return (0);
}

int	init_mutex(t_data *data)
{
	int	i;

	i = 0;
	data->fork = malloc(sizeof(pthread_mutex_t) * data->nb_philo);
	if (!data->fork)
		return (1);
	while (i < data->nb_philo)
	{
		if (pthread_mutex_init(&data->fork[i], NULL) != 0)
			return (1);
		i++;
	}
	if (pthread_mutex_init(&data->lock_data, NULL) != 0)
		return (1);
	return (0);
}