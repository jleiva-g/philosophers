/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleiva-g <jleiva-g@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 16:27:44 by jleiva-g          #+#    #+#             */
/*   Updated: 2025/11/09 05:41:38 by jleiva-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

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
	if (mode > 1)
		pthread_mutex_destroy(&table->smutex);
	if (mode > 2)
		pthread_mutex_destroy(&table->wmutex);
	return (1);
}

int	cleanup(t_table *table)
{
	free_return(table, 1);
	free(table->threads);
	return (1);
}
