/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleiva-g <jleiva-g@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 16:27:44 by jleiva-g          #+#    #+#             */
/*   Updated: 2025/11/10 19:32:02 by jleiva-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	destroy_forks_mutex(t_table *table, int i, int mode)
{
	if (mode)
		free(table->forks[i].mutex);
	while (i--)
	{
		pthread_mutex_destroy(table->forks[i].mutex);
		free(table->forks[i].mutex);
	}
	free(table->forks);
	return (1);
}

int	destroy_philos_mutex(t_table *table, int i, int mode)
{
	if (mode > 1)
		pthread_mutex_destroy(table->philos[i].lmutex);
	if (mode)
		free(table->philos[i].lmutex);
	if (mode > 2)
		free(table->philos[i].mmutex);
	while (i--)
	{
		pthread_mutex_destroy(table->philos[i].lmutex);
		free(table->philos[i].lmutex);
		pthread_mutex_destroy(table->philos[i].mmutex);
		free(table->philos[i].mmutex);
	}
	free(table->philos);
	return (1);
}

int	free_return(t_table *table, int mode)
{
	destroy_forks_mutex(table, table->nphilos, 0);
	if (mode)
		destroy_philos_mutex(table, table->nphilos, 0);
	if (mode > 2)
		pthread_mutex_destroy(table->smutex);
	if (mode > 1)
		free(table->smutex);
	if (mode > 4)
		pthread_mutex_destroy(table->wmutex);
	if (mode > 3)
		free(table->wmutex);
	return (1);
}

int	cleanup(t_table *table)
{
	free_return(table, 5);
	free(table->threads);
	return (1);
}
