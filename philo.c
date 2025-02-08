/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pemirand <pemirand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 19:18:45 by pemirand          #+#    #+#             */
/*   Updated: 2025/02/04 21:07:18 by pemirand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philo.h"

int	main(int argc, char **argv)
{
	t_pgr	*pgr;
	int		i;

	pgr = init_pgr(argc, argv);
	if (pgr)
	{
		i = 0;
		while (i < pgr->n_philos)
		{
			pthread_create(&pgr->philos[i]->thread, NULL, \
						&philo_routine, pgr->philos[i]);
			i++;
		}
		i = 0;
		pthread_create(&pgr->m_thread, NULL, &monitoring_routine, pgr);
		pthread_join(pgr->m_thread, NULL);
		while (i < pgr->n_philos)
		{
			pthread_join(pgr->philos[i]->thread, NULL);
			i++;
		}
		mutex_destroy(pgr);
		free_pgr(pgr);
	}
	return (0);
}
