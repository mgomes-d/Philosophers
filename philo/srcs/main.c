/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgomes-d <mgomes-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 08:56:20 by mgomes-d          #+#    #+#             */
/*   Updated: 2023/03/31 10:24:23 by mgomes-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_data		data;

	if ((ac != 5 && ac != 6) || ft_check_args(av))
		return (error_exit(&data, MSG_ARG, 0, 0));
	if (init_struct(&data, av, ac))
		return (1);
	if (join_threads(&data, data.nb_philo))
		return (error_exit(&data, MSG_THREAD, 4, data.nb_philo));
	if (destroy_mutex(&data, data.nb_philo))
		return (error_exit(&data, MSG_MUTEX, 4, data.nb_philo));
	free_everthing(&data);
	return (0);
}
