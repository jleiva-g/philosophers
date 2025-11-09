/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleiva-g <jleiva-g@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 19:40:45 by jleiva-g          #+#    #+#             */
/*   Updated: 2025/11/09 04:38:13 by jleiva-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo_bonus.h"

static void	check_input(char **argv)
{
	int	i;
	int	j;

	i = 0;
	while (argv[++i])
	{
		j = -1;
		while (argv[i][++j])
			if (argv[i][j] < '0' || argv[i][j] > '9')
				exit(1);
	}
}

static void	init_sem(t_table *table)
{
	sem_unlink("/fork");
	table->forks_sem = sem_open("/fork", O_CREAT, S_IRWXU, table->nphilos);
	if (!table->forks_sem)
		exit(1);
	sem_unlink("/death");
	table->death_sem = sem_open("/death", O_CREAT, S_IRWXU, 0);
	if (!table->death_sem)
		clear_sem(table, 0);
	sem_unlink("/meals");
	table->meals_sem = sem_open("/meals", O_CREAT, S_IRWXU, 0);
	if (!table->meals_sem)
		clear_sem(table, 1);
	sem_unlink("/print");
	table->print_sem = sem_open("/print", O_CREAT, S_IRWXU, 1);
	if (!table->print_sem)
		clear_sem(table, 2);
	sem_unlink("/sigterm");
	table->sigterm_sem = sem_open("/sigterm", O_CREAT, S_IRWXU, 0);
	if (!table->sigterm_sem)
		clear_sem(table, 3);
}

static void	init_philos(t_table *table)
{
	int	i;

	table->philos = malloc(sizeof(t_philo) * table->nphilos);
	if (!table->philos)
	{
		clear_sem(table, 3);
		exit(1);
	}
	i = -1;
	while (++i < table->nphilos)
	{
		table->philos[i].id = i + 1;
		table->philos[i].table = table;
		table->philos[i].last_meal = 0;
		table->philos[i].meals = 0;
	}
}

static void	init_children(t_table *table)
{
	int	i;

	table->children = malloc(sizeof(t_philo) * table->nphilos);
	if (!table->children)
	{
		clear_sem(table, 4);
		free(table->philos);
		exit(1);
	}
	i = -1;
	while (++i < table->nphilos)
	{
		table->children[i] = fork();
		if (!table->children[i])
			start_routine(&table->philos[i]);
		else if (table->children[i] == -1)
		{
			wait_children(table, i);
			clear_sem(table, 4);
			free(table->philos);
			pthread_mutex_destroy(&table->mutex);
			free(table->children);
			exit(1);
		}
	}
}

void	init(t_table *table, int argc, char **argv)
{
	check_input(argv);
	table->nphilos = ft_atol(argv[1]);
	table->tdie = ft_atol(argv[2]);
	table->teat = ft_atol(argv[3]);
	table->tsleep = ft_atol(argv[4]);
	if (table->nphilos > 400 || !table->nphilos || !table->tdie
		|| !table->teat || !table->tsleep)
		exit(1);
	if (argc == 6)
		table->max_meals = ft_atol(argv[5]);
	else
		table->max_meals = -1;
	table->status = 1;
	init_sem(table);
	init_philos(table);
	if (pthread_mutex_init(&table->mutex, NULL))
	{
		clear_sem(table, 4);
		free(table->philos);
		exit(1);
	}
	table->stime = get_time(0);
	init_children(table);
}
