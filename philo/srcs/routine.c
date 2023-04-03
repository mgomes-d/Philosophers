/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgomes-d <mgomes-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 09:41:53 by mgomes-d          #+#    #+#             */
/*   Updated: 2023/04/03 07:59:53 by mgomes-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	sleeping(t_philo *philo)
{
	int	time;

	pthread_mutex_lock(&philo->data->lock_data);
	time = philo->data->time_to_sleep;
	pthread_mutex_unlock(&philo->data->lock_data);
	show_msg(philo, MSG_SLEEP);
	ft_usleep(time);
	return ;
}

int	eating(t_philo *philo, int nb_philo)
{
	pthread_mutex_lock(philo->right_fork);
	show_msg(philo, MSG_FORK);
	if (nb_philo == 1)
	{
		pthread_mutex_unlock(philo->right_fork);
		return (1);
	}
	pthread_mutex_lock(philo->left_fork);
	show_msg(philo, MSG_FORK);
	show_msg(philo, MSG_EAT);
	pthread_mutex_lock(&philo->data->lock_data);
	philo->time_last_meal = get_time();
	pthread_mutex_unlock(&philo->data->lock_data);
	ft_usleep(philo->data->time_to_eat);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_lock(&philo->data->lock_data);
	philo->meals_time += 1;
	pthread_mutex_unlock(&philo->data->lock_data);
	return (0);
}

void	thinking(t_philo *philo)
{
	show_msg(philo, MSG_THINK);
	return ;
}

void	*routine(void *philo_ptr)
{
	t_philo	*philo;
	int		must_eat;
	bool	is_alive;
	int		nb_philo;

	philo = philo_ptr;
	pthread_mutex_lock(&philo->data->lock_data);
	must_eat = philo->data->nb_must_eat;
	is_alive = philo->data->is_alive;
	nb_philo = philo->data->nb_philo;
	pthread_mutex_unlock(&philo->data->lock_data);
	while (is_alive && (must_eat > 0 || must_eat == -2))
	{
		if (eating(philo_ptr, nb_philo))
			break ;
		sleeping(philo_ptr);
		thinking(philo_ptr);
		pthread_mutex_lock(&philo->data->lock_data);
		is_alive = philo->data->is_alive;
		pthread_mutex_unlock(&philo->data->lock_data);
	}
	return (NULL);
}
