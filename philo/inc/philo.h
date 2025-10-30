/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleiva-g <jleiva-g@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 16:07:29 by jleiva-g          #+#    #+#             */
/*   Updated: 2025/10/30 16:53:38 by jleiva-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>

typedef struct s_data
{
	int				nphilos;
	long			tdie;
	long			teat;
	long			tsleep;
	long			max_meals;
	int				status;
	pthread_t		*philos;
	pthread_mutex_t	*forks;
	pthread_mutex_t	*mutex;
}	t_data;

typedef struct s_philo
{
	int				id;
	struct s_data	data;
	long			last_meal;
	long			meals;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*mutex;
}	t_philo;

// utils
long	get_time(long time);
long	ft_atol(char *nptr);
// init
void	init(t_data *data, int argc, char **argv);

#endif
