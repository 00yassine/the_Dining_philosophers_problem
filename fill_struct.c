/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykabili- <ykabili-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 12:06:34 by ykabili-          #+#    #+#             */
/*   Updated: 2025/04/30 17:35:38 by ykabili-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_free_struct(t_data *data)
{
	free(data->philos);
	free(data->tid_arr);
	return (1);
}

static int	init_philos(t_data *data)
{
	pthread_mutex_t		*mutex_arr;
	int					i;

	i = 0;
	mutex_arr = malloc(sizeof(pthread_mutex_t) * data->nb_of_philos);
	if (!mutex_arr)
		return (ft_free_struct(data));
	while (i < data->nb_of_philos)
	{
		pthread_mutex_init(&mutex_arr[i], NULL);
		data->philos[i].id = i + 1;
		data->philos[i].last_meal = 0;
		data->philos[i].meals_count = 0;
		data->philos[i].mutex = mutex_arr;
		data->philos[i].data = data;
		pthread_mutex_init(&data->philos[i].meal_prot, NULL);
		pthread_mutex_init(&data->philos[i].count_prot, NULL);
		i++;
	}
	return (0);
}

int	fill_struct(char **av, int ac, t_data *data)
{
	data->nb_of_philos = ft_atoi(av[1]);
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	data->nb_of_meals = 0;
	if (ac == 6)
		data->nb_of_meals = ft_atoi(av[5]);
	data->is_dead = 1;
	data->tid_arr = malloc(sizeof(pthread_t) * data->nb_of_philos);
	if (!data->tid_arr)
		return (1);
	data->philos = malloc(sizeof(t_philo) * data->nb_of_philos);
	if (!data->philos)
	{
		free(data->tid_arr);
		return (1);
	}
	pthread_mutex_init(&data->print, NULL);
	pthread_mutex_init(&data->m_death, NULL);
	data->start_time = get_time();
	return (init_philos(data));
}
