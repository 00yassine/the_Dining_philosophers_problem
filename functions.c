/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykabili- <ykabili-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 15:13:26 by ykabili-          #+#    #+#             */
/*   Updated: 2025/05/01 11:31:02 by ykabili-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_status(t_philo *philo, char *str)
{
	long int	time;

	time = get_time() - philo->data->start_time;
	pthread_mutex_lock(&philo->data->print);
	printf("\e[0;32m %ld %d %s", time, philo->id, str);
	pthread_mutex_lock(&philo->data->m_death);
	if (philo->data->is_dead == 0)
	{
		pthread_mutex_unlock(&philo->data->m_death);
		return ;
	}
	pthread_mutex_unlock(&philo->data->print);
	pthread_mutex_unlock(&philo->data->m_death);
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
	print_status(philo, "is sleeping");
	ft_usleep(philo->data->time_to_sleep);
	print_status(philo, "is thinking");
}

void	check_death(t_philo *philos)
{
	pthread_mutex_lock(&philos->meal_prot);
	if (get_time() - philos->last_meal >= philos->data->time_to_die)
	{
		pthread_mutex_unlock(&philos->meal_prot);
		pthread_mutex_lock(&philos->data->m_death);
		philos->data->is_dead = 0;
		pthread_mutex_unlock(&philos->data->m_death);
		print_status(philos, "died");
	}
	else
		pthread_mutex_unlock(&philos->meal_prot);
}
