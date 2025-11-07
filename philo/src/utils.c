/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleiva-g <jleiva-g@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 10:33:04 by jleiva-g          #+#    #+#             */
/*   Updated: 2025/11/07 17:03:12 by jleiva-g         ###   ########.fr       */
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

void	print_status(t_table *table, int philo, char mode)
{
	char	*str;

	str = "";
	if (mode == 'f')
		str = "\e[33m\0has taken a fork\e[0m";
	else if (mode == 'e')
		str = "\e[32m\0is eating\e[0m";
	else if (mode == 's')
		str = "\e[34m\0is sleeping\e[0m";
	else if (mode == 't')
		str = "\e[35m\0is thinking\e[0m";
	else if (mode == 'd')
		str = "\e[31m\0died\e[0m";
	pthread_mutex_lock(&table->wmutex);
	printf("%s%06li %i %s\n", str, get_time(table->stime), philo, str + 6);
	pthread_mutex_unlock(&table->wmutex);
}
