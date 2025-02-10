/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pemirand <pemirand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 19:00:38 by pemirand          #+#    #+#             */
/*   Updated: 2025/02/10 15:59:36 by pemirand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	philo_eat(t_philo *philo, pthread_mutex_t *f1, pthread_mutex_t *f2)
{
	int				res;

	res = EXIT_FAILURE;
	pthread_mutex_lock(f1);
	if (check_dead_flag(philo->table))
		return (pthread_mutex_unlock(f1), res);
	printf("%ld %d has taken a fork\n", get_time_ms() - \
			philo->table->start_time, philo->id);
	if (f1 == f2)
		return (pthread_mutex_unlock(f1), res);
	pthread_mutex_lock(f2);
	update_last_meal(philo, get_time_ms());
	if (check_dead_flag(philo->table) == 0)
	{
		printf("%ld %d has taken a fork\n", \
			get_time_ms() - philo->table->start_time, philo->id);
		printf("%ld %d is eating\n", \
			get_time_ms() - philo->table->start_time, philo->id);
		philo->meals_eaten++;
		res = ft_wait(philo->table->time_to_eat, philo);
	}
	pthread_mutex_unlock(f1);
	return (pthread_mutex_unlock(f2), res);
}

int	philo_sleep(t_philo *philo)
{
	if (check_dead_flag(philo->table) == 0)
	{
		printf("%ld %d is sleeping\n", \
			get_time_ms() - philo->table->start_time, philo->id);
		return (ft_wait(philo->table->time_to_sleep, philo));
	}
	return (EXIT_FAILURE);
}

int	philo_think(t_philo *philo)
{
	if (check_dead_flag(philo->table) == 0)
	{
		printf("%ld %d is thinking\n", \
			get_time_ms() - philo->table->start_time, philo->id);
		return (EXIT_SUCCESS);
	}
	return (EXIT_FAILURE);
}

void	*philo_routine(void *data)
{
	t_philo	*philo;
	int		res;

	philo = (t_philo *)data;
	add_created_thread(philo->table);
	while (check_created_threads(philo->table) != 1)
		;
	update_last_meal(philo, philo->table->start_time);
	while (1)
	{
		if (philo->id % 2 == 1)
			usleep(500);
		if (philo->id % 2 == 0)
			res = philo_eat(philo, philo->right_fork, &philo->left_fork);
		else
			res = philo_eat(philo, &philo->left_fork, philo->right_fork);
		if (res == EXIT_FAILURE)
			return (NULL);
		if (philo->meals_eaten == philo->table->eats_to_full)
			return (add_full_eaten(philo->table), NULL);
		if (philo_sleep(philo) == EXIT_FAILURE || \
			philo_think(philo) == EXIT_FAILURE)
			return (NULL);
	}
	return (NULL);
}
