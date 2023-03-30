/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgomes-d <mgomes-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 07:49:40 by mgomes-d          #+#    #+#             */
/*   Updated: 2023/03/30 11:26:31 by mgomes-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *str)
{
	long	nb;
	int		i;

	i = 0;
	nb = 0;
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

int	get_time(void)
{
	struct timeval	time;

	if ((gettimeofday(&time, NULL)) == -1)
		return (-1);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

int	get_time_philo(t_philo *philo)
{
	int				time;
	int				final_time;

	pthread_mutex_lock(&philo->data->lock_data);
	time = get_time();
	final_time = time - philo->data->start_time;
	pthread_mutex_unlock(&philo->data->lock_data);
	return (final_time);
}

void	ft_usleep(int ms)
{
	int	start;

	start = get_time();
	while (get_time() - start < ms)
		usleep(100);
}

void	show_msg(t_philo *philo, char *msg)
{
	int	time;
	int	is_alive;

	pthread_mutex_lock(&philo->data->lock_data);
	is_alive = philo->data->is_alive;
	pthread_mutex_unlock(&philo->data->lock_data);
	time = get_time_philo(philo);
	if (is_alive)
		printf("%d %d %s\n", time, philo->philo_id, msg);
	return ;
}
