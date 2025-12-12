/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleiva-g <jleiva-g@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 16:27:44 by jleiva-g          #+#    #+#             */
/*   Updated: 2025/12/12 18:57:31 by jleiva-g         ###   ########.fr       */
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

static void	clear_sem_continued(t_table *table, int mode)
{
	if (mode > 4)
	{
		sem_close(table->status_sem);
		sem_unlink("/status");
	}
	if (mode > 5)
	{
		sem_close(table->sigterm_sem);
		sem_unlink("/sigterm");
	}
	else
		exit(1);
}

void	clear_sem(t_table *table, int mode)
{
	sem_close(table->forks_sem);
	sem_unlink("/forks");
	if (mode)
	{
		sem_close(table->plate_sem);
		sem_unlink("/plate");
	}
	if (mode > 1)
	{
		sem_close(table->death_sem);
		sem_unlink("/death");
	}
	if (mode > 2)
	{
		sem_close(table->meals_sem);
		sem_unlink("/meals");
	}
	if (mode > 3)
	{
		sem_close(table->print_sem);
		sem_unlink("/print");
	}
	clear_sem_continued(table, mode);
}

void	free_exit(t_table *table, int mode)
{
	clear_sem(table, 6);
	free(table->philos);
	if (mode > 1)
		pthread_mutex_destroy(table->mutex);
	if (mode)
		free(table->mutex);
	if (mode > 2)
		free(table->children);
	exit(1);
}

void	cleanup(t_table *table)
{
	wait_children(table, table->nphilos);
	clear_sem(table, 6);
	free(table->philos);
	pthread_mutex_destroy(table->mutex);
	free(table->mutex);
	free(table->children);
}
