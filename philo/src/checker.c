/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleiva-g <jleiva-g@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 17:34:39 by jleiva-g          #+#    #+#             */
/*   Updated: 2025/11/04 01:24:13 by jleiva-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	checker(t_table *table)
{
	int		i;
	long	last_meal;
	long	meals;

	while (1)
	{
		i = -1;
		while (++i < table->nphilos)
		{
			last_meal = get_var(&table->philos[i].last_meal,
					&table->philos[i].lmutex);
			if (get_time(table->stime) - last_meal > table->tdie)
			{
				set_var(&table->status, &table->smutex, i + 1);
				print_status(table, i + 1, 'd');
				return ;
			}
			meals = get_var(&table->philos[i].meals, &table->philos[i].mmutex);
			if (table->max_meals > -1 && table->max_meals <= meals)
			{
				set_var(&table->status, &table->smutex, -1);
				return ;
			}
		}
	}
}
