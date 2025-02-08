/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pemirand <pemirand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 14:27:43 by pemirand          #+#    #+#             */
/*   Updated: 2025/02/04 21:35:09 by pemirand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_pgr		t_pgr;
typedef struct s_philo		t_philo;

typedef struct s_philo
{
	pthread_t				thread;
	int						id;
	int						n_times_to_eat;
	unsigned long int		last_meal;
	pthread_mutex_t			left_fork;
	pthread_mutex_t			*right_fork;
	t_pgr					*pgr;
}	t_philo;

typedef struct s_pgr
{
	pthread_t				m_thread;
	int						n_philos;
	unsigned long int		time_to_die;
	unsigned long int		time_to_eat;
	unsigned long int		time_to_sleep;
	int						n_times_to_eat;
	int						dead_flag;
	long int				start_time;
	t_philo					**philos;
}	t_pgr;

unsigned long int	*check_args(int argc, char **argv);
t_pgr				*init_pgr(int argc, char **argv);
t_pgr				*new_pgr(unsigned long int n_philos, \
							unsigned long int time_to_die, \
							unsigned long int time_to_eat, \
							unsigned long int time_to_sleep);
t_philo				*new_philo(int id, t_pgr *pgr);
int					start_pgr(t_pgr *pgr);
t_pgr				*init_pgr(int argc, char **argv);
void				free_philos(t_philo **philos, int size);
void				free_pgr(t_pgr *pgr);
long int			get_time_ms(void);
void				*philo_routine(void *data);
void				*monitoring_routine(void *data);
int					ft_wait(long int ms, t_philo *philo);
void				mutex_destroy(t_pgr *pgr);
void				print_philo(t_philo *philo);
void				print_pgr(t_pgr *pgr);
#endif
