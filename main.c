/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykabili- <ykabili-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 20:44:07 by ykabili-          #+#    #+#             */
/*   Updated: 2025/04/30 14:00:51 by ykabili-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
	return (0);
}
