/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgomes-d <mgomes-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 08:56:20 by mgomes-d          #+#    #+#             */
/*   Updated: 2023/03/24 10:32:08 by mgomes-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	cmp = 0;

int	ft_check_args(char **av)
{
	int	i;
	int	j;

	i = 1;
	while (av[i])
	{
		j = 0;
		while (av[i][j])
		{
			if (av[i][j] >= 48 && av[i][j] <= 57)
				j++;
			else
				return (1);
		}
		i++;
	}
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
	return (0);
}

int	eating(t_philo *philo)
{
	(void)philo;
	pthread_mutex_lock(philo->left_fork);
	printf("philo %d has taken a fork\n", philo->philo_id);
	pthread_mutex_lock(philo->right_fork);
	printf("philo %d has taken a fork\n", philo->philo_id);
	printf("philo %d is eating\n", philo->philo_id);
	pthread_mutex_unlock(philo->left_fork);
 	pthread_mutex_unlock(philo->right_fork);
	usleep(50000);
	 return (0);
}

void	*routine(void *philo_ptr)
{
	int	i;

	i = 0;
	// while (i++ < 5)
	// {
	// 	write(2, "fd\n", 3);
		eating(philo_ptr);
//	}
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

int	error_exit(t_data *data)
{
	(void)data;
	write(2, "ERROR\n", 6);
	return (1);
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
		i++;
	}
	return (0);
}

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
	return (0);
}

// int	check_data(t_data *data)
// {
// 	if (data->nb_philo <= 0)
// 		return (1);
// 	return (0);
// }

int	init_struct(t_data *data, char **av, int ac)
{
	data->nb_philo = ft_atoi(av[1]);
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		data->nb_must_eat = ft_atoi(av[5]);
	if (init_mutex(data))
		return (1);
	if (init_philo(data))
		return (1);
	if (init_thread(data))
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