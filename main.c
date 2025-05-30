/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykabili- <ykabili-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 20:44:07 by ykabili-          #+#    #+#             */
/*   Updated: 2025/05/29 17:43:17 by ykabili-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	single_philo(t_data *data)
{
	print_status(&data->philos[0], "has taken a fork\n", "\033[0;35m");
	ft_usleep(data->time_to_die);
	print_status(&data->philos[0], "is dead\n", "\033[0;31m");
}

int	free_data(t_data *data)
{
	free (data);
	return (print_error("error!!!"));
}

int	print_error(char *str)
{
	printf("\e[0;31m%s", str);
	return (1);
}

static void	free_all(t_data *data)
{
	if (data->philos[0].mutex)
		free(data->philos[0].mutex);
	if (data->philos)
		free(data->philos);
	if (data->tid_arr)
		free(data->tid_arr);
	if (data)
		free(data);
}

int	main(int ac, char **av)
{
	t_data	*data;

	if (ac != 5 && ac != 6)
		return (print_error("the number of arguments is not valid!!!"));
	if (check_arguments(av))
		return (print_error("the arguments are not numbers or not valid!!!"));
	data = malloc(sizeof(t_data));
	if (fill_struct(av, ac, data))
		return (free_data(data));
	if (data->nb_of_philos == 1)
	{
		single_philo(data);
		free_all(data);
	}
	else if (launch_threads(data))
	{
		free_all(data);
		return (1);
	}
	return (0);
}
