/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleiva-g <jleiva-g@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 17:34:39 by jleiva-g          #+#    #+#             */
/*   Updated: 2025/11/14 18:43:54 by jleiva-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static void	set_status(t_table *table, long new_value)
{
	pthread_mutex_lock(table->smutex);
	table->status = new_value;
	pthread_mutex_unlock(table->smutex);
}

static int	check_last_meal(t_philo *philo)
{
	long	time;
	long	last_meal;

	time = get_time(philo->table->stime);
	pthread_mutex_lock(philo->lmutex);
	last_meal = philo->last_meal;
	pthread_mutex_unlock(philo->lmutex);
	if (time - last_meal > philo->table->tdie)
	{
		set_status(philo->table, philo->id);
		print_status(philo->table, philo->id, 'd');
		return (1);
	}
	return (0);
}

static int	check_max_meals(t_philo *philo)
{
	int	meals;

	pthread_mutex_lock(philo->mmutex);
	meals = philo->meals;
	pthread_mutex_unlock(philo->mmutex);
	if (philo->table->max_meals <= meals)
	{
		pthread_mutex_lock(philo->mmutex);
		philo->meals = -1;
		pthread_mutex_unlock(philo->mmutex);
		return (1);
	}
	return (0);
}

void	checker(t_table *table)
{
	int		i;
	int		max_eaten;

	max_eaten = 0;
	while (1)
	{
		i = -1;
		while (++i < table->nphilos)
		{
			if (check_last_meal(&table->philos[i]))
				return ;
			if (table->max_meals > -1 && check_max_meals(&table->philos[i]))
			{
				max_eaten++;
				if (max_eaten == table->nphilos)
				{
					set_status(table, -1);
					return ;
				}
			}
		}
		usleep(100);
	}
}
