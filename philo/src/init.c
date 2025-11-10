/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleiva-g <jleiva-g@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 19:40:45 by jleiva-g          #+#    #+#             */
/*   Updated: 2025/11/10 19:36:36 by jleiva-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static int	init_forks(t_table *table)
{
	int	i;

	table->forks = malloc(table->nphilos * sizeof(t_fork));
	if (!table->forks)
		return (1);
	i = -1;
	while (++i < table->nphilos)
	{
		table->forks[i].is_taken = 0;
		table->forks[i].mutex = malloc(sizeof(pthread_mutex_t));
		if (!table->forks[i].mutex)
			return (destroy_forks_mutex(table, i, 0));
		if (pthread_mutex_init(table->forks[i].mutex, NULL))
			return (destroy_forks_mutex(table, i, 1));
	}
	return (0);
}

static int	init_single_philo(t_table *table, int id)
{
	table->philos[id].id = id + 1;
	table->philos[id].table = table;
	table->philos[id].last_meal = 0;
	table->philos[id].meals = 0;
	if (!id)
		table->philos[id].left_fork = &table->forks[table->nphilos - 1];
	else
		table->philos[id].left_fork = &table->forks[id - 1];
	table->philos[id].right_fork = &table->forks[id];
	table->philos[id].lmutex = malloc(sizeof(pthread_mutex_t));
	if (!table->philos[id].lmutex)
		return (destroy_forks_mutex(table, id, 0));
	if (pthread_mutex_init(table->philos[id].lmutex, NULL))
		return (destroy_philos_mutex(table, id, 1));
	table->philos[id].mmutex = malloc(sizeof(pthread_mutex_t));
	if (!table->philos[id].mmutex)
		return (destroy_forks_mutex(table, id, 2));
	if (pthread_mutex_init(table->philos[id].mmutex, NULL))
		return (destroy_philos_mutex(table, id, 3));
	return (0);
}

static int	init_philos(t_table *table)
{
	int	i;

	table->philos = malloc(table->nphilos * sizeof(t_philo));
	if (!table->philos)
		return (1);
	i = -1;
	while (++i < table->nphilos)
		if (init_single_philo(table, i))
			return (1);
	return (0);
}

static int	init_allocs(t_table *table)
{
	if (init_forks(table))
		return (1);
	if (init_philos(table))
		return (free_return(table, 0));
	table->smutex = malloc(sizeof(pthread_mutex_t));
	if (!table->smutex)
		return (free_return(table, 1));
	if (pthread_mutex_init(table->smutex, NULL))
		return (free_return(table, 2));
	table->wmutex = malloc(sizeof(pthread_mutex_t));
	if (!table->wmutex)
		return (free_return(table, 3));
	if (pthread_mutex_init(table->wmutex, NULL))
		return (free_return(table, 4));
	table->threads = malloc(table->nphilos * sizeof(pthread_t));
	if (!table->threads)
		return (free_return(table, 5));
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
	if (init_allocs(table))
		return (1);
	return (0);
}
