/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleiva-g <jleiva-g@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 17:34:39 by jleiva-g          #+#    #+#             */
/*   Updated: 2025/10/31 19:06:18 by jleiva-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	checker(t_table *table)
{
	int	i;

	while (1)
	{
		i = -1;
		while (++i < table->nphilos)
		{
			pthread_mutex_lock(&table->philos[i].mutex);
			pthread_mutex_lock(&table->mutex);
			if (get_time(table->stime) - table->philos[i].last_meal
				> table->tdie)
			{
				table->status = i + 1;
				print_status(table, i, 'd');
			}
			if (table->max_meals <= table->philos[i].meals)
				table->status = -1;
			pthread_mutex_unlock(&table->philos[i].mutex);
			pthread_mutex_unlock(&table->mutex);
		}
	}
	return (0);
}
