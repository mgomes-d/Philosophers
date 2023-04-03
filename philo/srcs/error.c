/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgomes-d <mgomes-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 07:41:56 by mgomes-d          #+#    #+#             */
/*   Updated: 2023/04/03 08:42:31 by mgomes-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	join_threads_error(t_data *data, int size)
{
	while (size)
	{
		if (pthread_join(data->philosophers[size], NULL) != 0)
			return (1);
		size--;
	}
	return (0);
}

int	destroy_mutex_error(t_data *data, int size)
{
	while (size)
	{
		if (pthread_mutex_destroy(&data->fork[size]) != 0)
			break ;
		size--;
	}
	if (pthread_mutex_destroy(&data->lock_data) != 0)
		return (1);
	return (0);
}

void	error_utils(t_data *data, int i, int size)
{
	if (i == 1)
		destroy_mutex(data, size);
	if (i == 2)
		destroy_mutex(data, size);
	if (i == 3)
	{
		if (i == 4)
		{
			destroy_mutex_error(data, size);
			join_threads_error(data, size);
		}
		else
		{
			destroy_mutex(data, size);
			join_threads(data, size);
		}
	}
}

int	error_exit(t_data *data, char *msg, int i, int size)
{
	int	index;

	index = 0;
	while (msg[index])
		index++;
	write (2, msg, index);
	error_utils(data, i, size);
	if (i >= 1)
		free(data->fork);
	if (i >= 2)
		free(data->philo);
	if (i >= 3)
		free(data->philosophers);
	return (1);
}

void	free_everthing(t_data *data)
{
	if (data->fork)
		free(data->fork);
	if (data->philo)
		free(data->philo);
	if (data->philosophers)
		free(data->philosophers);
}
