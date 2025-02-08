/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pemirand <pemirand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 22:38:54 by pemirand          #+#    #+#             */
/*   Updated: 2025/02/04 21:41:28 by pemirand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	philo_eat(t_philo *philo)
{
	int		wait_flag;

	wait_flag = EXIT_FAILURE;
	pthread_mutex_lock(&philo->left_fork);
	if (philo->pgr->dead_flag)
	{
		pthread_mutex_unlock(&philo->left_fork);
		return (EXIT_FAILURE);
	}
	printf("%ld %d has taken a fork\n", get_time_ms() - \
			philo->pgr->start_time, philo->id);
	if (&philo->left_fork == philo->right_fork)
		return (pthread_mutex_unlock(&philo->left_fork), EXIT_FAILURE);
	pthread_mutex_lock(philo->right_fork);
	if (philo->pgr->dead_flag == 0)
	{
		printf("%ld %d has taken a fork\n", \
			get_time_ms() - philo->pgr->start_time, philo->id);
		printf("%ld %d is eating\n", \
			get_time_ms() - philo->pgr->start_time, philo->id);
		wait_flag = ft_wait(philo->pgr->time_to_eat, philo);
	}
	pthread_mutex_unlock(&philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	return (wait_flag);
}

int	philo_sleep(t_philo *philo)
{
	int		wait_flag;

	wait_flag = EXIT_FAILURE;
	if (philo->pgr->dead_flag == 0)
	{
		printf("%ld %d is sleeping\n", \
			get_time_ms() - philo->pgr->start_time, philo->id);
		wait_flag = ft_wait(philo->pgr->time_to_sleep, philo);
	}
	return (wait_flag);
}

void	*philo_routine(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	if (philo->id % 2 == 0)
		usleep(500);
	while (philo->n_times_to_eat != 0)
	{
		if (philo_eat(philo) == EXIT_FAILURE)
			return (NULL);
		philo->last_meal = get_time_ms();
		philo->n_times_to_eat++;
		if (philo->n_times_to_eat != 0)
		{
			if (philo_sleep(philo) == EXIT_FAILURE)
				return (NULL);
			if (philo->pgr->dead_flag == 0)
				printf("%ld %d is thinking\n", \
					get_time_ms() - philo->pgr->start_time, philo->id);
		}
	}
	return (NULL);
}

void	dead_philho(t_pgr *pgr, int id)
{
	pgr->dead_flag = 1;
	printf("%ld %d died\n", get_time_ms() - pgr->start_time, id);
}

void	*monitoring_routine(void *data)
{
	int		i;
	int		fineshed;
	t_pgr	*pgr;

	pgr = (t_pgr *)data;
	i = 0;
	fineshed = 0;
	while (pgr->dead_flag == 0)
	{
		if (get_time_ms() - pgr->philos[i]->last_meal >= pgr->time_to_die)
			return (dead_philho(pgr, i + 1), NULL);
		else if (pgr->philos[i]->n_times_to_eat == 0)
			fineshed++;
		if (fineshed == pgr->n_philos)
			pgr->dead_flag = 1;
		i++;
		if (i == pgr->n_philos)
		{
			i = 0;
			fineshed = 0;
		}
	}
	return (NULL);
}
