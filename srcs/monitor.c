/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pemirand <pemirand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 19:36:55 by pemirand          #+#    #+#             */
/*   Updated: 2025/02/11 16:27:04 by pemirand         ###   ########.fr       */
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
			print_message(table, 'd', dead_philo);
			return ;
		}
		if (check_full_eaten(table))
			return ;
		usleep(500);
	}
}
