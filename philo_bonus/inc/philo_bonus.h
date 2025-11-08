/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleiva-g <jleiva-g@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 16:07:29 by jleiva-g          #+#    #+#             */
/*   Updated: 2025/11/08 04:32:12 by jleiva-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H
# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <signal.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <semaphore.h>

typedef struct s_philo
{
	int				id;
	struct s_table	*table;
	long			last_meal;
	long			meals;
	sem_t			*fork_sem;
	sem_t			*death_sem;
	sem_t			*meals_sem;
	sem_t			*print_sem;
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
	struct s_philo	*philos;
	pid_t			*children;
	pthread_t		death_checker;
	pthread_t		meals_checker;
	pthread_mutex_t	mutex;
	sem_t			*forks_sem;
	sem_t			*death_sem;
	sem_t			*meals_sem;
	sem_t			*print_sem;
}	t_table;

// utils
long	ft_atol(char *nptr);
long	get_time(long time);
void	print_status(t_table *table, int philo, char mode);
// init
void	init(t_table *table, int argc, char **argv);
// routine
void	routine(void *param);
// checker
void	checker(t_table *table);
// cleanup
void	clear_sem(t_table *table);
int		destroy_forks_mutex(t_table *table, int i);
int		destroy_philos_mutex(t_table *table, int i, int mode);
int		free_return(t_table *table, int mode);
int		cleanup(t_table *table);

#endif
