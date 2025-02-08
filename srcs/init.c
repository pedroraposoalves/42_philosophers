/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pemirand <pemirand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 14:29:25 by pemirand          #+#    #+#             */
/*   Updated: 2025/02/04 21:08:27 by pemirand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	init_mutex(t_pgr *pgr)
{
	int	i;

	if (!pgr)
		return (EXIT_FAILURE);
	if (!pgr->philos)
		return (EXIT_FAILURE);
	i = 0;
	while (i < pgr->n_philos)
		pthread_mutex_init(&(pgr->philos[i++]->left_fork), NULL);
	i = 0;
	while (i++ < pgr->n_philos)
	{
		if (i < pgr->n_philos)
			pgr->philos[i - 1]->right_fork = &(pgr->philos[i]->left_fork);
		else
			pgr->philos[pgr->n_philos - 1]->right_fork = \
				&(pgr->philos[0]->left_fork);
	}
	return (EXIT_SUCCESS);
}

t_pgr	*new_pgr(unsigned long int n_philos, unsigned long int time_to_die, \
	unsigned long int time_to_eat, unsigned long int time_to_sleep)
{
	t_pgr	*pgr;

	pgr = (t_pgr *)malloc(sizeof(t_pgr));
	if (!pgr)
		return (NULL);
	pgr->start_time = get_time_ms();
	pgr->n_philos = n_philos;
	pgr->time_to_die = time_to_die;
	pgr->time_to_eat = time_to_eat;
	pgr->time_to_sleep = time_to_sleep;
	pgr->n_times_to_eat = -1;
	pgr->dead_flag = 0;
	pgr->philos = NULL;
	return (pgr);
}

t_philo	*new_philo(int id, t_pgr *pgr)
{
	t_philo	*philo;

	philo = (t_philo *)malloc(sizeof(t_philo));
	if (!philo)
		return (NULL);
	philo->id = id;
	philo->n_times_to_eat = pgr->n_times_to_eat * -1;
	philo->last_meal = pgr->start_time;
	philo->pgr = pgr;
	return (philo);
}

int	start_pgr(t_pgr *pgr)
{
	int	i;

	if (!pgr)
		return (EXIT_FAILURE);
	pgr->philos = (t_philo **)malloc(sizeof(t_philo *) * pgr->n_philos);
	if (!pgr->philos)
		return (EXIT_FAILURE);
	i = 0;
	while (i < pgr->n_philos)
	{
		pgr->philos[i] = new_philo(i + 1, pgr);
		if (pgr->philos[i] == NULL)
		{
			free_philos(pgr->philos, pgr->n_philos);
			pgr->philos = NULL;
			return (EXIT_FAILURE);
		}
		i++;
	}
	init_mutex(pgr);
	i = 0;
	return (EXIT_SUCCESS);
}

t_pgr	*init_pgr(int argc, char **argv)
{
	t_pgr				*pgr;
	unsigned long int	*args;

	args = check_args(argc, argv);
	if (args == NULL)
		return (NULL);
	pgr = new_pgr(args[0], args[1], args[2], args[3]);
	if (argc == 6)
		pgr->n_times_to_eat = args[4];
	free(args);
	if (!pgr)
		return (NULL);
	if (start_pgr(pgr) == EXIT_FAILURE)
		return (free_pgr(pgr), NULL);
	return (pgr);
}
