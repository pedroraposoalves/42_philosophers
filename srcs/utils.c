/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pemirand <pemirand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 17:40:50 by pemirand          #+#    #+#             */
/*   Updated: 2025/02/10 17:47:05 by pemirand         ###   ########.fr       */
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
			if (ft_isonlydigits(argv[i - 1]) == EXIT_SUCCESS \
				&& ft_atoi(argv[i - 1]) > 0)
				res[i - 2] = ft_atoi(argv[i - 1]);
			else
			{
				printf("Error: Invalid Args: ");
				printf("You should submit only numbers bigger than 0\n");
				return (free(res), NULL);
			}
		}
	}
	else
		printf("Error: Invalid Args: You Should submit 4 or 5 numbers\n");
	return (res);
}

unsigned long int	get_time_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

int	ft_wait(unsigned long int ms, t_philo *philo)
{
	unsigned long int	now;

	now = get_time_ms();
	while (get_time_ms() - now < ms)
	{
		if (check_dead_flag(philo->table))
			return (EXIT_FAILURE);
		usleep(500);
	}
	return (EXIT_SUCCESS);
}
