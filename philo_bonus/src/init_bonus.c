/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleiva-g <jleiva-g@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 19:40:45 by jleiva-g          #+#    #+#             */
/*   Updated: 2025/12/13 09:54:29 by jleiva-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo_bonus.h"

static void	set_sem_name(t_philo *philo)
{
	philo->sem_name[0] = '/';
	philo->sem_name[1] = (philo->id / 100) % 10 + '0';
	philo->sem_name[2] = (philo->id / 10) % 10 + '0';
	philo->sem_name[3] = philo->id % 10 + '0';
	philo->sem_name[4] = '\0';
}

static void	init_philos(t_table *table)
{
	int	i;

	table->philos = malloc(sizeof(t_philo) * table->nphilos);
	if (!table->philos)
	{
		close_sems(table, 6);
		exit(EXIT_FAILURE);
	}
	i = -1;
	while (++i < table->nphilos)
	{
		table->philos[i].id = i + 1;
		table->philos[i].table = table;
		table->philos[i].last_meal = 0;
		table->philos[i].meals = 0;
		set_sem_name(&(table->philos[i]));
	}
}

static void	init_sem(t_table *table)
{
	unlink_sems(6);
	table->forks_sem = sem_open("/forks", O_CREAT, 0644, table->nphilos);
	if (table->forks_sem == SEM_FAILED)
		exit(EXIT_FAILURE);
	table->plate_sem = sem_open("/plate", O_CREAT, 0644, table->nphilos / 2);
	if (table->plate_sem == SEM_FAILED)
		close_sems(table, 0);
	table->death_sem = sem_open("/death", O_CREAT, 0644, 0);
	if (table->death_sem == SEM_FAILED)
		close_sems(table, 1);
	table->meals_sem = sem_open("/meals", O_CREAT, 0644, 0);
	if (table->meals_sem == SEM_FAILED)
		close_sems(table, 2);
	table->print_sem = sem_open("/print", O_CREAT, 0644, 1);
	if (table->print_sem == SEM_FAILED)
		close_sems(table, 3);
	table->status_sem = sem_open("/status", O_CREAT, 0644, 1);
	if (table->status_sem == SEM_FAILED)
		close_sems(table, 4);
	table->sigterm_sem = sem_open("/sigterm", O_CREAT, 0644, 0);
	if (table->sigterm_sem == SEM_FAILED)
		close_sems(table, 5);
}

static void	init_children(t_table *table)
{
	int	i;

	table->children = malloc(sizeof(t_philo) * table->nphilos);
	if (!table->children)
	{
		close_sems(table, 6);
		free(table->philos);
		exit(EXIT_FAILURE);
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
			close_sems(table, 6);
			free(table->philos);
			free(table->children);
			exit(EXIT_FAILURE);
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
		exit(EXIT_FAILURE);
	if (argc == 6)
		table->max_meals = ft_atol(argv[5]);
	else
		table->max_meals = -1;
	table->status = 1;
	init_sem(table);
	init_philos(table);
	table->stime = get_time(0);
	init_children(table);
}
