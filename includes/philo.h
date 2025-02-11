/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pemirand <pemirand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 14:27:43 by pemirand          #+#    #+#             */
/*   Updated: 2025/02/11 16:18:06 by pemirand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_table		t_table;
typedef struct s_philo		t_philo;

typedef struct s_philo
{
	pthread_t			thread;
	int					id;
	int					meals_eaten;
	unsigned long		last_meal;
	pthread_mutex_t		left_fork;
	pthread_mutex_t		*right_fork;
	pthread_mutex_t		last_meal_mutex;
	t_table				*table;
}	t_philo;

typedef struct s_table
{
	pthread_t			thread;
	int					n_philos;
	unsigned long		time_to_die;
	unsigned long		time_to_eat;
	unsigned long		time_to_sleep;
	int					eats_to_full;
	int					full_eaten;
	int					dead_flag;
	int					created_threads;
	unsigned long		start_time;
	pthread_mutex_t		print_mutex;
	pthread_mutex_t		dead_flag_mutex;
	pthread_mutex_t		full_eaten_mutex;
	pthread_mutex_t		created_threads_mutex;
	t_philo				**philos;
}	t_table;

/*****************INIT********************/
t_table			*init_table(int argc, char **argv);

/*****************UTILS********************/
unsigned long	*check_args(int argc, char **argv);
unsigned long	get_time_ms(void);
unsigned long	ft_atoi(char *str);
int				ft_wait(unsigned long ms, t_philo *philo);

/*****************TABLE********************/
void			*philo_routine(void *data);
void			monitor(t_table *table);

/*****************MUTEX********************/
void			add_created_thread(t_table *table);
int				check_created_threads(t_table *table);
int				check_dead_flag(t_table *table);
void			set_dead_flag(t_table *table, int value);
int				check_full_eaten(t_table *table);
void			add_full_eaten(t_table *table);
void			update_last_meal(t_philo *philo, size_t timestamp);
int				philo_is_dead(t_philo *philo);
unsigned long	get_philo_last_meal(t_philo *philo);
void			print_message(t_table *table, char flag, int d);

/*****************FREE********************/
void			free_philos(t_philo **philos, int size);
void			free_table(t_table *table);
#endif
