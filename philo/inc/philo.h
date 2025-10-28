/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleiva-g <jleiva-g@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 16:07:29 by jleiva-g          #+#    #+#             */
/*   Updated: 2025/10/28 20:01:56 by jleiva-g         ###   ########.fr       */
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

typedef struct s_philo
{
	int		index;
	long	last_eat;
	long	times_eat;
}	t_philo;

typedef struct s_data
{
	int		nphilos;
	long	tdie;
	long	teat;
	long	tsleep;
	long	must_eat;
}	t_data;

// utils
long	get_time(long time);
long	ft_atol(char *nptr);
// init
void	init(t_data *data, int argc, char **argv);

#endif
