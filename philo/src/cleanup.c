/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleiva-g <jleiva-g@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 16:27:44 by jleiva-g          #+#    #+#             */
/*   Updated: 2025/11/07 17:29:51 by jleiva-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	cleanup(t_table *table)
{
	int	i;

	pthread_mutex_destroy(&table->smutex);
	pthread_mutex_destroy(&table->wmutex);
	i = -1;
	while (++i < table->nphilos)
	{
		pthread_mutex_destroy(&table->forks[i].mutex);
		pthread_mutex_destroy(&table->philos[i].lmutex);
		pthread_mutex_destroy(&table->philos[i].mmutex);
	}
	free(table->forks);
	free(table->philos);
	free(table->threads);
}
