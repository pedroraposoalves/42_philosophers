/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pemirand <pemirand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 17:37:27 by pemirand          #+#    #+#             */
/*   Updated: 2025/02/10 12:42:10 by pemirand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philo.h"

void	print_philo(t_philo *philo)
{
	printf("\t\tPhilo ID\t: %d\n", philo->id);
	printf("\t\tMeals eaten\t: %d\n", philo->meals_eaten);
	printf("\t\tLast Meal\t: %lu\n", philo->last_meal);
	printf("\t\tLeft Fork\t: %p\n", &philo->left_fork);
	printf("\t\tRight Fork\t: %p\n", philo->right_fork);
}

void	print_table(t_table *table)
{
	int	i;

	printf("Program :\n\tNR Philosphers\t: %d\n", table->n_philos);
	printf("\tTime to die\t: %lu\n", table->time_to_die);
	printf("\tTime to eat\t: %lu\n", table->time_to_eat);
	printf("\tTime to sleep\t: %lu\n", table->time_to_sleep);
	printf("\tEats Full\t: %d\n", table->eats_to_full);
	printf("\tDead Flag\t: %d\n", table->dead_flag);
	printf("\tStart time\t: %lu\n", table->start_time);
	if (table->philos == NULL)
		return ;
	i = 0;
	printf("\n\tPhilos :\n");
	while (i < table->n_philos)
	{
		print_philo(table->philos[i]);
		i++;
	}
}

void	print_philos_eaten(t_philo **list, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		printf("Philo: %d \t|\t", list[i]->id);
		printf(" Eaten\t: %d\t->", list[i]->meals_eaten);
		printf(" Gap\t: %lu\n", get_time_ms() - list[i]->last_meal);
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_table	*table;
	int		i;

	table = init_table(argc, argv);
	if (!table)
		return (1);
	table->start_time = get_time_ms();
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
