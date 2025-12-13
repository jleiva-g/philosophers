/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleiva-g <jleiva-g@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 16:07:29 by jleiva-g          #+#    #+#             */
/*   Updated: 2025/12/13 13:10:34 by jleiva-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include <sys/time.h>
# include <pthread.h>

typedef struct s_fork
{
	int				is_taken;
	pthread_mutex_t	*mutex;
}	t_fork;

typedef struct s_philo
{
	int				id;
	struct s_table	*table;
	long			last_meal;
	long			meals;
	t_fork			*left_fork;
	t_fork			*right_fork;
	pthread_mutex_t	*lmutex;
	pthread_mutex_t	*mmutex;
}	t_philo;

typedef struct s_table
{
	int				nphilos;
	long			stime;
	long			tdie;
	long			teat;
	long			tsleep;
	long			max_meals;
	int				status;
	pthread_t		*threads;
	t_philo			*philos;
	t_fork			*forks;
	pthread_mutex_t	*smutex;
	pthread_mutex_t	*wmutex;
}	t_table;

// utils
int		check_input(char **argv);
int		ph_atoi(char *nptr);
long	get_time(long time);
void	print_status(t_table *table, int philo, char mode);
// init
int		init(t_table *table, int argc, char **argv);
// routine
void	*routine(void *param);
// checker
void	checker(t_table *table);
// cleanup
int		destroy_forks_mutex(t_table *table, int i, int mode);
int		destroy_philos_mutex(t_table *table, int i, int mode);
int		free_return(t_table *table, int mode);
int		cleanup(t_table *table);

#endif
