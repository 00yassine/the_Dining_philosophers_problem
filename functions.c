/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykabili- <ykabili-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 15:13:26 by ykabili-          #+#    #+#             */
/*   Updated: 2025/04/30 15:48:22 by ykabili-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_status(t_philo *philo, char *str)
{
	pthread_mutex_lock(&philo->data->print);
	printf("\e[0;32m %ld %d %s", get_time() - philo->data->start_time, str);
	pthread_mutex_lock(&philo->data->m_death);
	if (philo->data->is_dead == 0)
	{
		pthread_mutex_unlock(&philo->data->m_death);
		return ;
	}
	pthread_mutex_unlock(&philo->data->print);
	pthread_mutex_unlock(&philo->data->m_death);
}
