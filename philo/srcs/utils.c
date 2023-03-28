/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgomes-d <mgomes-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 07:49:40 by mgomes-d          #+#    #+#             */
/*   Updated: 2023/03/28 11:18:02 by mgomes-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *str)
{
	long	nb;
	int		i;

	i = 0;
	while (str[i] >= 48 && str[i] <= 57)
	{
		nb = nb * 10 + str[i] - 48;
		if (nb > INT_MAX)
			return (-1);
		if (nb < INT_MIN)
			return (-1);
		i++;
	}
	return (nb);
}

int	get_time(t_philo *philo)
{
	struct timeval	time;
	int				time_int;
	int				final_time;

	pthread_mutex_lock(&philo->data->lock_data);
	if ((gettimeofday(&time, 0)) == -1)
		return (-1);
	time_int = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	final_time = time_int - philo->data->start_time;
	pthread_mutex_unlock(&philo->data->lock_data);
	return (final_time);
}
