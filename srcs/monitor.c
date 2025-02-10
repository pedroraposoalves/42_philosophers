/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pemirand <pemirand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 19:36:55 by pemirand          #+#    #+#             */
/*   Updated: 2025/02/10 17:17:08 by pemirand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	check_dead_philos(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->n_philos)
	{
		if (philo_is_dead(table->philos[i]))
			return (i);
		i++;
	}
	return (-1);
}

void	monitor(t_table *table)
{
	int	dead_philo;

	while (check_created_threads(table) != 1)
		;
	usleep (500);
	while (1)
	{
		dead_philo = check_dead_philos(table) + 1;
		if (dead_philo > 0)
		{
			printf("%lu %d died\n", \
				get_time_ms() - table->start_time, dead_philo);
			set_dead_flag(table, 1);
			return ;
		}
		if (check_full_eaten(table))
			return ;
		usleep(500);
	}
}
