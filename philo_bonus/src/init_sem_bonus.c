/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_sem_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleiva-g <jleiva-g@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 18:40:45 by jleiva-g          #+#    #+#             */
/*   Updated: 2025/12/12 18:56:48 by jleiva-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo_bonus.h"

static void	init_sem_continued(t_table *table)
{
	table->sigterm_sem = sem_open("/sigterm", O_CREAT, 0644, 0);
	if (table->sigterm_sem == SEM_FAILED)
		clear_sem(table, 5);
}

void	init_sem(t_table *table)
{
	sem_unlink("/forks");
	sem_unlink("/plate");
	sem_unlink("/death");
	sem_unlink("/meals");
	sem_unlink("/print");
	sem_unlink("/status");
	sem_unlink("/sigterm");
	table->forks_sem = sem_open("/forks", O_CREAT, 0644, table->nphilos);
	if (table->forks_sem == SEM_FAILED)
		exit(1);
	table->plate_sem = sem_open("/plate", O_CREAT, 0644, table->nphilos / 2);
	if (table->plate_sem == SEM_FAILED)
		clear_sem(table, 0);
	table->death_sem = sem_open("/death", O_CREAT, 0644, 0);
	if (table->death_sem == SEM_FAILED)
		clear_sem(table, 1);
	table->meals_sem = sem_open("/meals", O_CREAT, 0644, 0);
	if (table->meals_sem == SEM_FAILED)
		clear_sem(table, 2);
	table->print_sem = sem_open("/print", O_CREAT, 0644, 1);
	if (table->print_sem == SEM_FAILED)
		clear_sem(table, 3);
	table->status_sem = sem_open("/status", O_CREAT, 0644, 1);
	if (table->print_sem == SEM_FAILED)
		clear_sem(table, 4);
}
