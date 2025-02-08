/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pemirand <pemirand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 21:31:39 by pemirand          #+#    #+#             */
/*   Updated: 2025/02/04 21:36:48 by pemirand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	ft_isonlydigits(char *str)
{
	int	c;

	while (*str)
	{
		c = *str;
		if (!(c >= '0' && c <= '9'))
			return (EXIT_FAILURE);
		str++;
	}
	return (EXIT_SUCCESS);
}

unsigned long int	ft_atoi(char *str)
{
	unsigned long int	res;

	res = 0;
	while (*str)
	{
		res = res * 10 + *str - '0';
		str++;
	}
	return (res);
}

unsigned long int	*check_args(int argc, char **argv)
{
	unsigned long int	*res;
	int					i;

	res = NULL;
	if (argc > 4 && argc < 7)
	{
		i = 1;
		res = (unsigned long int *)malloc(sizeof(unsigned long int) * \
				(argc - 1));
		while (i++ < argc)
		{
			if (ft_isonlydigits(argv[i - 1]) == EXIT_SUCCESS)
				res[i - 2] = ft_atoi(argv[i - 1]);
			else
			{
				printf("Error: Invalid Args: ");
				printf("You should submit only numbers bigger than 0\n");
				free(res);
				return (NULL);
			}
		}
	}
	else
		printf("Error: Invalid Args: You Should submit 4 or 5 numbers");
	return (res);
}

long int	get_time_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

int	ft_wait(long int ms, t_philo *philo)
{
	long int	now;

	now = get_time_ms();
	while (get_time_ms() - now < ms)
	{
		if (philo->pgr->dead_flag == 1)
			return (EXIT_FAILURE);
		usleep(500);
	}
	return (EXIT_SUCCESS);
}

/*void	print_philo(t_philo *philo)
{
	printf("\t\tPhilo ID\t: %d\n", philo->id);
	printf("\t\tMust eat\t: %d\n", philo->n_times_to_eat);
	printf("\t\tStart Time\t: %lu\n", philo->pgr->start_time);
	printf("\t\tLast Meal\t: %lu\n", philo->last_meal);
}

void	print_pgr(t_pgr *pgr)
{
	int	i;

	i = 0;
	printf("Program :\n\tNR Philosphers\t: %d\n", pgr->n_philos);
	printf("\tTime to die\t: %lu\n", pgr->time_to_die);
	printf("\tTime to eat\t: %lu\n", pgr->time_to_eat);
	printf("\tTime to sleep\t: %lu\n", pgr->time_to_sleep);
	printf("\tMust Eat\t: %d\n", pgr->n_times_to_eat);
	printf("\tStart time\t: %lu\n", pgr->start_time);
	if (pgr->philos == NULL)
		return ;
	printf("\n\tPhilos :\n");
	while (i < pgr->n_philos)
	{
		print_philo(pgr->philos[i]);
		i++;
	}
}*/
