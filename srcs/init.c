/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pemirand <pemirand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 17:38:44 by pemirand          #+#    #+#             */
/*   Updated: 2025/02/11 16:12:09 by pemirand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

t_table	*new_table(unsigned long n_philos, unsigned long time_to_die, \
	unsigned long time_to_eat, unsigned long time_to_sleep)
{
	t_table	*table;

	table = (t_table *)malloc(sizeof(t_table));
	if (!table)
		return (NULL);
	table->n_philos = n_philos;
	table->time_to_die = time_to_die;
	table->time_to_eat = time_to_eat;
	table->time_to_sleep = time_to_sleep;
	table->eats_to_full = 0;
	table->full_eaten = 0;
	table->dead_flag = 0;
	table->created_threads = 0;
	table->start_time = 0;
	pthread_mutex_init(&table->print_mutex, NULL);
	pthread_mutex_init(&table->dead_flag_mutex, NULL);
	pthread_mutex_init(&table->full_eaten_mutex, NULL);
	pthread_mutex_init(&table->created_threads_mutex, NULL);
	table->philos = NULL;
	return (table);
}

t_philo	*new_philo(int id, t_table *table)
{
	t_philo	*philo;

	philo = (t_philo *)malloc(sizeof(t_philo));
	if (!philo)
		return (NULL);
	philo->id = id;
	philo->meals_eaten = 0;
	philo->last_meal = 0;
	pthread_mutex_init(&philo->left_fork, NULL);
	pthread_mutex_init(&philo->last_meal_mutex, NULL);
	philo->right_fork = NULL;
	philo->table = table;
	return (philo);
}

int	init_philos(t_table *table)
{
	int	i;

	if (!table)
		return (EXIT_FAILURE);
	table->philos = (t_philo **)malloc(sizeof(t_philo *) * table->n_philos);
	if (!table->philos)
		return (EXIT_FAILURE);
	i = 0;
	while (i < table->n_philos)
	{
		table->philos[i] = new_philo(i + 1, table);
		if (table->philos[i] == NULL)
		{
			free_philos(table->philos, table->n_philos);
			table->philos = NULL;
			return (EXIT_FAILURE);
		}
		if (i > 0)
			table->philos[i - 1]->right_fork = &table->philos[i]->left_fork;
		i++;
	}
	table->philos[i - 1]->right_fork = &table->philos[0]->left_fork;
	return (EXIT_SUCCESS);
}

t_table	*init_table(int argc, char **argv)
{
	t_table			*table;
	unsigned long	*args;

	args = check_args(argc, argv);
	if (args == NULL)
		return (NULL);
	table = new_table(args[0], args[1], args[2], args[3]);
	if (argc == 6)
		table->eats_to_full = args[4];
	free(args);
	if (!table)
		return (NULL);
	if (init_philos(table) == EXIT_FAILURE)
		return (free_table(table), NULL);
	return (table);
}
