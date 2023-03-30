/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgomes-d <mgomes-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 07:41:56 by mgomes-d          #+#    #+#             */
/*   Updated: 2023/03/30 11:21:35 by mgomes-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	error_exit(t_data *data, char *msg, int i)
{
	int	index;

	index = 0;
	while (msg[index])
		index++;
	write (2, msg, index);
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
