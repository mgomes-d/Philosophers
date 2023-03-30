/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgomes-d <mgomes-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 09:41:53 by mgomes-d          #+#    #+#             */
/*   Updated: 2023/03/30 11:37:15 by mgomes-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	sleeping(t_philo *philo)
{
	show_msg(philo, MSG_SLEEP);
	ft_usleep(philo->data->time_to_sleep);
	return (0);
}

int	eating(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	show_msg(philo, MSG_FORK);
	pthread_mutex_lock(philo->right_fork);
	show_msg(philo, MSG_FORK);
	show_msg(philo, MSG_EAT);
	pthread_mutex_lock(&philo->data->lock_data);
	philo->meals_time += 1;
	philo->time_last_meal = get_time();
	pthread_mutex_unlock(&philo->data->lock_data);
	ft_usleep(philo->data->time_to_eat);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	return (0);
}

int	thinking(t_philo *philo)
{
	show_msg(philo, MSG_THINK);
	return (0);
}

void	*routine(void *philo_ptr)
{
	t_philo	*philo;
	int		must_eat;
	bool	is_alive;

	philo = philo_ptr;
	pthread_mutex_lock(&philo->data->lock_data);
	must_eat = philo->data->nb_must_eat;
	is_alive = philo->data->is_alive;
	pthread_mutex_unlock(&philo->data->lock_data);
	while (is_alive && (must_eat > 0 || must_eat == -2))
	{
		eating(philo_ptr);
		sleeping(philo_ptr);
		thinking(philo_ptr);
		printf("%d\n", is_alive);
		pthread_mutex_lock(&philo->data->lock_data);
		is_alive = philo->data->is_alive;
		pthread_mutex_unlock(&philo->data->lock_data);
	}
	return (NULL);
}
