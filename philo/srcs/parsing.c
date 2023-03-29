/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgomes-d <mgomes-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 10:52:34 by mgomes-d          #+#    #+#             */
/*   Updated: 2023/03/29 11:10:43 by mgomes-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	struct_check(t_data *data)
{
	if (data->nb_philo <= 0)
		return (1);
	if (data->time_to_die <= 0)
		return (1);
	if (data->time_to_eat <= 0)
		return (1);
	if (data->time_to_sleep <= 0)
		return (1);
	if (data->nb_must_eat == -1 || data->nb_must_eat == 0)
		return (1);
	return (0);
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
