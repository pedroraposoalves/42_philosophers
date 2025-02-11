/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pemirand <pemirand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 19:27:18 by pemirand          #+#    #+#             */
/*   Updated: 2025/02/11 16:22:01 by pemirand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	update_last_meal(t_philo *philo, size_t timestamp)
{
	pthread_mutex_lock(&philo->last_meal_mutex);
	philo->last_meal = timestamp;
	pthread_mutex_unlock(&philo->last_meal_mutex);
}

unsigned long	get_philo_last_meal(t_philo *philo)
{
	unsigned long	res;

	pthread_mutex_lock(&philo->last_meal_mutex);
	res = philo->last_meal;
	pthread_mutex_unlock(&philo->last_meal_mutex);
	if (res == 0)
		res = philo->table->start_time;
	return (res);
}

int	philo_is_dead(t_philo *philo)
{
	int	res;

	res = 0;
	if (get_time_ms() - get_philo_last_meal(philo) \
		>= philo->table->time_to_die)
	{
		res = 1;
		set_dead_flag(philo->table, 1);
	}
	return (res);
}

int	check_full_eaten(t_table *table)
{
	int	res;

	pthread_mutex_lock(&table->full_eaten_mutex);
	res = table->full_eaten == table->n_philos;
	pthread_mutex_unlock(&table->full_eaten_mutex);
	return (res);
}

void	add_full_eaten(t_table *table)
{
	pthread_mutex_lock(&table->full_eaten_mutex);
	table->full_eaten++;
	pthread_mutex_unlock(&table->full_eaten_mutex);
}
