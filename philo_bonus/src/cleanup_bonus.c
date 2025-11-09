/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleiva-g <jleiva-g@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 16:27:44 by jleiva-g          #+#    #+#             */
/*   Updated: 2025/11/09 04:08:18 by jleiva-g         ###   ########.fr       */
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

void	clear_sem(t_table *table, int mode)
{
	sem_close(table->forks_sem);
	sem_unlink("/forks");
	if (mode)
	{
		sem_close(table->death_sem);
		sem_unlink("/death");
	}
	if (mode > 1)
	{
		sem_close(table->meals_sem);
		sem_unlink("/meals");
	}
	if (mode > 2)
	{
		sem_close(table->print_sem);
		sem_unlink("/print");
	}
	if (mode > 3)
	{
		sem_close(table->sigterm_sem);
		sem_unlink("/sigterm");
	}
	else
		exit(1);
}

void	cleanup(t_table *table)
{
	wait_children(table, table->nphilos);
	clear_sem(table, 4);
	free(table->philos);
	pthread_mutex_destroy(&table->mutex);
	free(table->children);
}
