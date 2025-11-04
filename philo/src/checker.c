/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleiva-g <jleiva-g@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 17:34:39 by jleiva-g          #+#    #+#             */
/*   Updated: 2025/11/04 01:31:15 by jleiva-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static long	get_last_meal(t_philo philo)
{
	long	last_meal;

	pthread_mutex_lock(&philo.lmutex);
	last_meal = philo.last_meal;
	pthread_mutex_unlock(&philo.lmutex);
	return (last_meal);
}

static long	get_meals(t_philo philo)
{
	long	meals;

	pthread_mutex_lock(&philo.mmutex);
	meals = philo.meals;
	pthread_mutex_unlock(&philo.mmutex);
	return (meals);
}

static void	set_status(t_table *table, long new_value)
{
	pthread_mutex_lock(&table->smutex);
	table->status = new_value;
	pthread_mutex_unlock(&table->smutex);
}

void	checker(t_table *table)
{
	int		i;

	while (1)
	{
		i = -1;
		while (++i < table->nphilos)
		{
			if (get_time(table->stime) - get_last_meal(table->philos[i])
				> table->tdie)
			{
				set_status(table, i + 1);
				print_status(table, i + 1, 'd');
				return ;
			}
			if (table->max_meals > -1
				&& table->max_meals <= get_meals(table->philos[i]))
			{
				set_status(table, -1);
				return ;
			}
		}
	}
}
