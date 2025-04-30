/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykabili- <ykabili-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 20:44:50 by ykabili-          #+#    #+#             */
/*   Updated: 2025/04/30 17:32:09 by ykabili-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <limits.h>
# include <string.h>
# include <sys/time.h>

typedef struct s_philo
{
	int						id;
	pthread_t				tid;
	long int				last_meal;
	int						meals_count;
	pthread_mutex_t			*mutex;
	struct s_data			*data;
	pthread_mutex_t			meal_prot;
	pthread_mutex_t			count_prot;
}	t_philo;
typedef struct s_data
{
	int					nb_of_philos;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					nb_of_meals;
	long int			start_time;
	int					is_dead;
	t_philo				*philos;
	pthread_t			*tid_arr;
	pthread_mutex_t		print;
	pthread_mutex_t		m_death;
}	t_data;
int							main(int ac, char **av);
int							check_arguments(char **av);
int							print_error(char *str);
int							ft_atoi(const char *str);
long int					get_time(void);
int							fill_struct(char **av, int ac, t_data *data);
void						print_status(t_philo *philo, char *str);
void						ft_usleep(long int time);
void						sleep_think(t_philo *philo);
#endif
