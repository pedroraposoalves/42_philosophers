/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pemirand <pemirand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 12:52:08 by pemirand          #+#    #+#             */
/*   Updated: 2025/02/04 17:38:30 by pemirand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	mutex_destroy(t_pgr *pgr)
{
	int	i;

	i = 0;
	while (i < pgr->n_philos)
	{
		pthread_mutex_destroy(&(pgr->philos[i]->left_fork));
		i++;
	}
}

void	free_philos(t_philo **philos, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		free(philos[i]);
		i++;
	}
	free(philos);
}

void	free_pgr(t_pgr *pgr)
{
	if (pgr->philos != NULL)
		free_philos(pgr->philos, pgr->n_philos);
	free(pgr);
}
