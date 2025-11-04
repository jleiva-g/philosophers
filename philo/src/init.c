/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleiva-g <jleiva-g@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 19:40:45 by jleiva-g          #+#    #+#             */
/*   Updated: 2025/11/04 19:44:21 by jleiva-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static int	check_input(char **argv)
{
	int	i;
	int	j;

	i = 0;
	while (argv[++i])
	{
		j = -1;
		while (argv[i][++j])
			if (argv[i][j] < '0' || argv[i][j] > '9')
				return (1);
	}
	return (0);
}

static int	init_forks(t_table *table)
{
	int	i;

	table->forks = malloc(sizeof(t_fork) * table->nphilos);
	if (!table->forks)
		return (1);
	i = -1;
	while (++i < table->nphilos)
	{
		table->forks[i].is_taken = 0;
		pthread_mutex_init(&table->forks[i].mutex, NULL);
	}
	return (0);
}

static int	init_philos(t_table *table)
{
	int	i;

	table->philos = malloc(sizeof(t_philo) * table->nphilos);
	if (!table->philos)
	{
		free(table->forks);
		return (1);
	}
	i = -1;
	while (++i < table->nphilos)
	{
		table->philos[i].id = i + 1;
		table->philos[i].table = table;
		table->philos[i].last_meal = 0;
		table->philos[i].meals = 0;
		if (!i)
			table->philos[i].left_fork = &table->forks[table->nphilos - 1];
		else
			table->philos[i].left_fork = &table->forks[i - 1];
		table->philos[i].right_fork = &table->forks[i];
		pthread_mutex_init(&table->philos[i].lmutex, NULL);
		pthread_mutex_init(&table->philos[i].mmutex, NULL);
	}
	return (0);
}

static int	init_threads(t_table *table)
{
	table->threads = malloc(sizeof(pthread_t) * table->nphilos);
	if (!table->threads)
	{
		free(table->forks);
		free(table->philos);
		return (1);
	}
	return (0);
}

int	init(t_table *table, int argc, char **argv)
{
	if (check_input(argv))
		return (1);
	table->nphilos = ft_atol(argv[1]);
	table->tdie = ft_atol(argv[2]);
	table->teat = ft_atol(argv[3]);
	table->tsleep = ft_atol(argv[4]);
	if (table->nphilos > 400 || !table->nphilos || !table->tdie
		|| !table->teat || !table->tsleep)
		return (1);
	if (argc == 6)
		table->max_meals = ft_atol(argv[5]);
	else
		table->max_meals = -1;
	table->status = 0;
	if (init_forks(table))
		return (1);
	if (init_philos(table))
		return (1);
	pthread_mutex_init(&table->smutex, NULL);
	pthread_mutex_init(&table->wmutex, NULL);
	if (init_threads(table))
		return (1);
	return (0);
}
