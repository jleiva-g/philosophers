/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleiva-g <jleiva-g@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 16:27:44 by jleiva-g          #+#    #+#             */
/*   Updated: 2025/12/13 10:09:31 by jleiva-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo_bonus.h"

void	wait_children(t_table *table, int nmemb)
{
	int	i;

	i = -1;
	while (++i < nmemb)
		sem_post(table->sigterm_sem);
	i = -1;
	while (++i < nmemb)
		waitpid(table->children[i], NULL, 0);
}

void	unlink_sems(int mode)
{
	sem_unlink("/forks");
	if (mode)
		sem_unlink("/plate");
	if (mode > 1)
		sem_unlink("/death");
	if (mode > 2)
		sem_unlink("/meals");
	if (mode > 3)
		sem_unlink("/print");
	if (mode > 4)
		sem_unlink("/status");
	if (mode > 5)
		sem_unlink("/sigterm");
	else
		exit(EXIT_FAILURE);
}

void	close_sems(t_table *table, int mode)
{
	sem_close(table->forks_sem);
	if (mode)
		sem_close(table->plate_sem);
	if (mode > 1)
		sem_close(table->death_sem);
	if (mode > 2)
		sem_close(table->meals_sem);
	if (mode > 3)
		sem_close(table->print_sem);
	if (mode > 4)
		sem_close(table->status_sem);
	if (mode > 5)
		sem_close(table->sigterm_sem);
	if (mode <= 6)
		unlink_sems(mode);
}

void	child_cleanup(t_philo *philo, int exit_code)
{
	sem_post(philo->table->forks_sem);
	sem_post(philo->table->forks_sem);
	sem_post(philo->table->plate_sem);
	close_sems(philo->table, 7);
	if (philo->philo_sem != SEM_FAILED)
		sem_close(philo->philo_sem);
	sem_unlink(philo->sem_name);
	free(philo->table->children);
	free(philo->table->philos);
	exit(exit_code);
}

void	cleanup(t_table *table)
{
	wait_children(table, table->nphilos);
	close_sems(table, 6);
	free(table->philos);
	free(table->children);
}
