/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgomes-d <mgomes-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 08:56:20 by mgomes-d          #+#    #+#             */
/*   Updated: 2023/03/23 11:06:40 by mgomes-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	cmp = 0;
pthread_mutex_t	mutex;

void	*routine()
{
	int	i = 0;
	
	printf("test\n");
	while (i < 1000000)
	{
		pthread_mutex_lock(&mutex);
		i++;
		cmp++;
		pthread_mutex_unlock(&mutex);
	}
	sleep(3);
	printf("Ending thread\n");

	return (NULL);
}

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

int	condition(t_data *data)
{
	
}

int	init_thread(t_data *data)
{
	int	i;

	i = 0;
	data->philo = malloc(sizeof(t_philo) * data->nb_philo);
	if (!data->philo)
		return (1);
	while (i < data->nb_philo)
	{
		data->philo[i].philo_id = i + 1;
		data->philo[i].left_fork = data->fork[i];
		data->philo[i].right_fork = data->fork[i + 1];
		i++;
	}
	return (0);
}

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
	if (init_thread(data))
		return (1);
	return (0);
}

int	main(int ac, char **av)
{
	pthread_t	t1;
	pthread_t	t2;
	t_data		data;

	(void)av;
	(void)ac;
	if ((ac != 5 && ac != 6) || ft_check_args(av))
		return (1);
	pthread_mutex_init(&mutex, NULL);
	if (init_struct(&data, av, ac))
		return (1);
	if (pthread_create(&t1, NULL, &routine, NULL) != 0)
		return (1);
	if (pthread_create(&t2, NULL, &routine, NULL) != 0)
		return (1);
	if (pthread_join(t1, NULL) != 0)
		return (1);
	if (pthread_join(t2, NULL) != 0)
		return (1);
	pthread_mutex_destroy(&mutex);
	printf("i = %d\n", cmp);
	return (0);
}