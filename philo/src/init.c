/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleiva-g <jleiva-g@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 19:40:45 by jleiva-g          #+#    #+#             */
/*   Updated: 2025/10/31 18:45:17 by jleiva-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

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
		// table->philos[i].last_meal = get_time(table->stime);
		table->philos[i].meals = 0;
		if (!i)
			table->philos[i].left_fork = &table->forks[table->nphilos - 1];
		table->philos[i].right_fork = &table->forks[i];
		pthread_mutex_init(&table->philos[i].mutex, NULL);
	}
	return (0);
}

static int	init_threads(t_table *table)
{
	int	i;

	table->threads = malloc(sizeof(pthread_t) * table->nphilos);
	if (!table->threads)
	{
		free(table->forks);
		free(table->philos);
		return (1);
	}
	i = -1;
	// while (++i < table->nphilos)
	// 	pthread_create();
	return (0);
}

int	init(t_table *table, int argc, char **argv)
{
	table->nphilos = ft_atol(argv[1]);
	table->stime = get_time(0);
	table->tdie = ft_atol(argv[2]);
	table->teat = ft_atol(argv[3]);
	table->tsleep = ft_atol(argv[4]);
	if (argc == 6)
		table->max_meals = ft_atol(argv[5]);
	else
		table->max_meals = -1;
	table->status = 0;
	if (init_forks(table))
		return (1);
	if (init_philos(table))
		return (1);
	pthread_mutex_init(&table->mutex, NULL);
	if (init_threads(table))
		return (1);
	return (0);
}
