/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launcher_thread.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykabili- <ykabili-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 09:45:12 by ykabili-          #+#    #+#             */
/*   Updated: 2025/06/01 15:51:01 by ykabili-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_usleep_(size_t milliseconds)
{
	size_t	start;

	start = get_time();
	while ((get_time() - start) < milliseconds)
		usleep(500);
	return (0);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	pthread_mutex_lock(&philo->meal_prot);
	philo->last_meal = get_time();
	pthread_mutex_unlock(&philo->meal_prot);
	while (1)
	{
		if (philo->data->is_dead == 0)
			return (NULL);
		if (philo->data->nb_of_meals && \
		philo->meals_count == philo->data->nb_of_meals)
			return (0);
		eat(philo);
		sleep_think(philo);
		// ft_usleep_(10);
	}
	return (NULL);
}

int	launch_threads(t_data *data)
{
	int	i;

	i = 0;
	data->start_time = get_time();
	while (i < data->nb_of_philos)
	{
		if (pthread_create(&data->tid_arr[i], NULL, routine, &data->philos[i]))
			return (1);
		usleep(99);
		i++;
	}
	i = 0;
	while (data->is_dead)
	{
		check_meals(data);
		check_death(&data->philos[i]);
		i++;
		i = i % data->nb_of_philos;
		// usleep(500);
	}
	i = 0;
	while (i < data->nb_of_philos)
	{
		pthread_join(data->tid_arr[i], NULL);
		i++;
	}
	return (0);
}
