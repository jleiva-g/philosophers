/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleiva-g <jleiva-g@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 16:27:44 by jleiva-g          #+#    #+#             */
/*   Updated: 2025/11/08 04:32:20 by jleiva-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo_bonus.h"

void	clear_sem(t_table *table)
{
	sem_close(table->forks_sem);
	sem_unlink("/forks");
	sem_close(table->death_sem);
	sem_unlink("/death");
	sem_close(table->meals_sem);
	sem_unlink("/meals");
	sem_close(table->print_sem);
	sem_unlink("/print");
}

int	destroy_forks_mutex(t_table *table, int i)
{
	while (i--)
		pthread_mutex_destroy(&table->forks[i].mutex);
	return (1);
}

int	destroy_philos_mutex(t_table *table, int i, int mode)
{
	if (mode)
		pthread_mutex_destroy(&table->philos[i].lmutex);
	while (i--)
	{
		pthread_mutex_destroy(&table->philos[i].lmutex);
		pthread_mutex_destroy(&table->philos[i].mmutex);
	}
	return (1);
}

int	free_return(t_table *table, int mode)
{
	destroy_forks_mutex(table, table->nphilos);
	free(table->forks);
	if (mode)
	{
		destroy_philos_mutex(table, table->nphilos, 0);
		free(table->philos);
	}
	return (1);
}

int	cleanup(t_table *table)
{
	free_return(table, 1);
	free(table->threads);
	return (1);
}
