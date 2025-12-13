/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleiva-g <jleiva-g@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 10:33:04 by jleiva-g          #+#    #+#             */
/*   Updated: 2025/12/13 13:14:15 by jleiva-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo_bonus.h"

void	check_input(char **argv)
{
	int	i;
	int	j;

	i = 0;
	while (argv[++i])
	{
		j = -1;
		while (argv[i][++j])
			if (argv[i][j] < '0' || argv[i][j] > '9')
				exit(EXIT_FAILURE);
	}
}

int	ph_atoi(char *nptr)
{
	long	n;

	n = 0;
	while (*nptr)
	{
		n = n * 10 + *nptr - '0';
		if (n > INT_MAX)
			return (0);
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
	int		status;

	str = "";
	if (mode == 'f')
		str = "\e[93m\0has taken a fork\e[0m";
	else if (mode == 'e')
		str = "\e[92m\0is eating\e[0m";
	else if (mode == 's')
		str = "\e[94m\0is sleeping\e[0m";
	else if (mode == 't')
		str = "\e[95m\0is thinking\e[0m";
	else if (mode == 'd')
		str = "\e[91m\0died\e[0m";
	sem_wait(table->print_sem);
	sem_wait(table->status_sem);
	status = table->status;
	sem_post(table->status_sem);
	if (status)
		printf("%s%06li %i %s\n", str, get_time(table->stime), philo, str + 6);
	if (mode == 'd')
		usleep(10000);
	sem_post(table->print_sem);
}
