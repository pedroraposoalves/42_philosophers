/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pemirand <pemirand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 19:27:18 by pemirand          #+#    #+#             */
/*   Updated: 2025/02/10 16:01:07 by pemirand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	update_last_meal(t_philo *philo, size_t timestamp)
{
	pthread_mutex_lock(&philo->last_meal_mutex);
	philo->last_meal = timestamp;
	pthread_mutex_unlock(&philo->last_meal_mutex);
}

int	philo_is_dead(t_philo *philo)
{
	int	res;

	res = 0;
	pthread_mutex_lock(&philo->last_meal_mutex);
	if (get_time_ms() - philo->last_meal \
		>= philo->table->time_to_die)
		res = 1;
	pthread_mutex_unlock(&philo->last_meal_mutex);
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
