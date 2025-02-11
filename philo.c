/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pemirand <pemirand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 17:37:27 by pemirand          #+#    #+#             */
/*   Updated: 2025/02/11 16:31:59 by pemirand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philo.h"

int	main(int argc, char **argv)
{
	t_table	*table;
	int		i;

	table = init_table(argc, argv);
	if (!table)
		return (1);
	i = 0;
	while (i++ < table->n_philos)
		pthread_create(&table->philos[i - 1]->thread, NULL, \
			&philo_routine, table->philos[i - 1]);
	monitor(table);
	i = 0;
	while (i++ < table->n_philos)
		pthread_join(table->philos[i - 1]->thread, NULL);
	free_table(table);
	return (0);
}
