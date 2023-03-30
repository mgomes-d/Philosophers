/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgomes-d <mgomes-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 08:56:20 by mgomes-d          #+#    #+#             */
/*   Updated: 2023/03/30 11:20:42 by mgomes-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_data		data;

	if ((ac != 5 && ac != 6) || ft_check_args(av))
		return (error_exit(&data, MSG_ARG, 0));
	if (init_struct(&data, av, ac))
		return (1);
	if (join_threads(&data))
		return (error_exit(&data, MSG_THREAD, 3));
	if (destroy_mutex(&data))
		return (error_exit(&data, MSG_MUTEX, 3));
	free_everthing(&data);
	return (0);
}

//tests ./philo 5 800 200 200 7 ./philo 4 410 200 200./philo 4 310 200 200