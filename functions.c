/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykabili- <ykabili-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 15:13:26 by ykabili-          #+#    #+#             */
/*   Updated: 2025/05/31 19:45:59 by ykabili-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_status(t_philo *philo, char *str, const char *color)
{
	long int	time;

	if (philo->data->is_dead == 0)
		return ;
	time = get_time() - philo->data->start_time;
	pthread_mutex_lock(&philo->data->print);
	printf("%s %ld %d %s\n", color, time, philo->id, str);
	pthread_mutex_unlock(&philo->data->print);
}

void	ft_usleep(long int time)
{
	long int	current_time;

	current_time = get_time();
	while (get_time() - current_time < time)
		usleep(30);
}

void	sleep_think(t_philo *philo)
{
	if (philo->data->is_dead == 0)
		return ;
	print_status(philo, "is sleeping", "\033[0;33m");
	ft_usleep(philo->data->time_to_sleep);
	print_status(philo, "is thinking", "\033[0;36m");
}

void	check_death(t_philo *philos)
{
	long int	time;

	pthread_mutex_lock(&philos->meal_prot);
	if (get_time() - philos->last_meal >= philos->data->time_to_die)
	{
		pthread_mutex_unlock(&philos->meal_prot);
		pthread_mutex_lock(&philos->data->m_death);
		philos->data->is_dead = 0;
		pthread_mutex_unlock(&philos->data->m_death);
		pthread_mutex_lock(&philos->data->print);
		time = get_time() - philos->data->start_time;
		printf("%s %ld %d %s\n", "\033[0m", time, philos->id, "died");
		pthread_mutex_unlock(&philos->data->print);
	}
	else
		pthread_mutex_unlock(&philos->meal_prot);
}

void	check_meals(t_data *data)
{
	int	i;

	i = 0;
	while (data->nb_of_meals)
	{
		pthread_mutex_lock(&data->philos[i].count_prot);
		if (data->philos[i].meals_count < data->nb_of_meals)
		{
			pthread_mutex_unlock(&data->philos[i].count_prot);
			break ;
		}
		else
		{
			pthread_mutex_unlock(&data->philos[i].count_prot);
			i++;
		}
		if (i == data->nb_of_philos)
		{
			pthread_mutex_lock(&data->m_death);
			data->is_dead = 0;
			pthread_mutex_unlock(&data->m_death);
		}
	}
}
