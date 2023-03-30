/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgomes-d <mgomes-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 09:50:27 by mgomes-d          #+#    #+#             */
/*   Updated: 2023/03/30 11:26:44 by mgomes-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	join_threads(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philo)
	{
		if (pthread_join(data->philosophers[i], NULL) != 0)
			return (1);
		i++;
	}
	return (0);
}

int	destroy_mutex(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philo)
	{
		if (pthread_mutex_destroy(&data->fork[i]) != 0)
			return (1);
		i++;
	}
	if (pthread_mutex_destroy(&data->lock_data) != 0)
		return (1);
	return (0);
}
