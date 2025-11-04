/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleiva-g <jleiva-g@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 10:33:04 by jleiva-g          #+#    #+#             */
/*   Updated: 2025/11/03 23:46:55 by jleiva-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

long	ft_atol(char *nptr)
{
	long	n;

	n = 0;
	while (*nptr)
	{
		n = n * 10 + *nptr - '0';
		nptr++;
	}
	return (n);
}

long	get_time(long start_time)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000 - start_time);
}

long	get_var(void *var, pthread_mutex_t *mutex)
{
	long	*res;

	pthread_mutex_lock(mutex);
	res = (long *) var;
	pthread_mutex_unlock(mutex);
	return (*res);
}

void	set_var(void *var, pthread_mutex_t *mutex, long new_value)
{
	long	*nptr;

	nptr = (long *) var;
	pthread_mutex_lock(mutex);
	*nptr = new_value;
	pthread_mutex_unlock(mutex);
}

void	print_status(t_table *table, int philo, char mode)
{
	char	*str;

	if (mode == 'f')
		str = "has taken a fork";
	else if (mode == 'e')
		str = "is eating";
	else if (mode == 's')
		str = "is sleeping";
	else if (mode == 't')
		str = "is thinking";
	else if (mode == 'd')
		str = "died";
	pthread_mutex_lock(&table->wmutex);
	printf("%06li %i %s\n", get_time(table->stime), philo, str);
	pthread_mutex_unlock(&table->wmutex);
}
