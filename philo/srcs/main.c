/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgomes-d <mgomes-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 08:56:20 by mgomes-d          #+#    #+#             */
/*   Updated: 2023/03/29 11:16:02 by mgomes-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	sleeping(t_philo *philo)
{
	show_msg(philo, MSG_SLEEP);
	ft_usleep(philo->data->time_to_sleep);
	return (0);
}

int	counter_for_die(t_philo *philo)
{
	(void)philo;
	return (0);
}

int	eating(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	show_msg(philo, MSG_FORK);
	// pthread_mutex_lock(&philo->data->lock_data);
	// if (philo->data->nb_philo == 1 && !philo->data->is_alive)
	// {
	// 	pthread_mutex_unlock(&philo->data->lock_data);
	// 	pthread_mutex_unlock(philo->left_fork);
	// 	return (0);
	// }
	//pthread_mutex_unlock(&philo->data->lock_data);
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
	while (is_alive && (must_eat > 0 || must_eat == -1))
	{
		eating(philo_ptr);
		sleeping(philo_ptr);
		thinking(philo_ptr);
		pthread_mutex_lock(&philo->data->lock_data);
		is_alive = philo->data->is_alive;
		pthread_mutex_unlock(&philo->data->lock_data);
	}
	//printf("is alive = %d\n", is_alive);
	//philo->data->timestamp_ms = gettimeofday(&philo->data->test, 0);
	//printf("time = %ld\n", philo->data->test.tv_sec);
	return (NULL);
}

// void	*routine01()
// {
// 	int	i = 0;
	
// 	printf("test\n");
// 	while (i < 1000000)
// 	{
// 		pthread_mutex_lock(&mutex);
// 		i++;
// 		cmp++;
// 		pthread_mutex_unlock(&mutex);
// 	}
// 	sleep(3);
// 	printf("Ending thread\n");
// 	return (NULL);
// }

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

int	main(int ac, char **av)
{
	t_data		data;

	if ((ac != 5 && ac != 6) || ft_check_args(av))
		return (1);
	if (init_struct(&data, av, ac))
		return (1);
	join_threads(&data);
	if (destroy_mutex(&data))
		return (1);
	printf("end\n");
	return (0);
}

//tests ./philo 5 800 200 200 7 ./philo 4 410 200 200./philo 4 310 200 200