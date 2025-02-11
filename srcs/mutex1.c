/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pemirand <pemirand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 19:15:50 by pemirand          #+#    #+#             */
/*   Updated: 2025/02/11 16:27:45 by pemirand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	add_created_thread(t_table *table)
{
	pthread_mutex_lock(&table->created_threads_mutex);
	table->created_threads++;
	if (table->created_threads == table->n_philos)
		table->start_time = get_time_ms();
	pthread_mutex_unlock(&table->created_threads_mutex);
}

int	check_created_threads(t_table *table)
{
	int	res;

	res = 0;
	pthread_mutex_lock(&table->created_threads_mutex);
	if (table->created_threads == table->n_philos)
		res = 1;
	pthread_mutex_unlock(&table->created_threads_mutex);
	return (res);
}

int	check_dead_flag(t_table *table)
{
	int	res;

	pthread_mutex_lock(&table->dead_flag_mutex);
	res = table->dead_flag;
	pthread_mutex_unlock(&table->dead_flag_mutex);
	return (res);
}

void	set_dead_flag(t_table *table, int value)
{
	pthread_mutex_lock(&table->dead_flag_mutex);
	table->dead_flag = value;
	pthread_mutex_unlock(&table->dead_flag_mutex);
}

void	print_message(t_table *table, char flag, int d)
{
	pthread_mutex_lock(&table->print_mutex);
	if (flag == 'd')
		printf("%lu %d died\n", get_time_ms() - table->start_time, d);
	else if (flag == 'e')
		printf("%lu %d is eating\n", get_time_ms() - table->start_time, d);
	else if (flag == 'f')
		printf("%lu %d has taken a fork\n", \
			get_time_ms() - table->start_time, d);
	else if (flag == 's')
		printf("%lu %d is sleeping\n", get_time_ms() - table->start_time, d);
	else if (flag == 't')
		printf("%lu %d is thinking\n", get_time_ms() - table->start_time, d);
	pthread_mutex_unlock(&table->print_mutex);
}
