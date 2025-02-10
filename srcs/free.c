/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pemirand <pemirand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 12:52:08 by pemirand          #+#    #+#             */
/*   Updated: 2025/02/10 15:21:21 by pemirand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	free_philos(t_philo **philos, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		pthread_mutex_destroy(&(philos[i]->left_fork));
		pthread_mutex_destroy(&(philos[i]->last_meal_mutex));
		free(philos[i]);
		i++;
	}
	free(philos);
}

void	free_table(t_table *table)
{
	if (table->philos != NULL)
		free_philos(table->philos, table->n_philos);
	pthread_mutex_destroy(&table->dead_flag_mutex);
	pthread_mutex_destroy(&table->full_eaten_mutex);
	pthread_mutex_destroy(&table->created_threads_mutex);
	free(table);
}
