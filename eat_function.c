/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat_function.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykabili- <ykabili-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 14:39:22 by ykabili-          #+#    #+#             */
/*   Updated: 2025/05/01 14:51:14 by ykabili-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->mutex[philo->id - 1]);
	print_status(philo, "has taken a fork", "\033[0;35m");
	pthread_mutex_lock(&philo->mutex[philo-> id % philo->data->nb_of_philos]);
	print_status(philo, "has taken a fork", "\033[0;35m");
	print_status(philo, "is eating", "\033[0;32m");
	pthread_mutex_lock(&philo->meal_prot);
	philo->last_meal = get_time();
	pthread_mutex_unlock(&philo->meal_prot);
	pthread_mutex_lock(&philo->count_prot);
	philo->meals_count++;
	pthread_mutex_unlock(&philo->count_prot);
	ft_usleep(philo->data->time_to_eat);
	pthread_mutex_unlock(&philo->mutex[philo->id -1]);
	pthread_mutex_unlock(&philo->mutex[philo->id % philo->data->nb_of_philos]);
}
