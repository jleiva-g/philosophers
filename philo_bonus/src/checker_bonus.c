/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleiva-g <jleiva-g@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 17:34:39 by jleiva-g          #+#    #+#             */
/*   Updated: 2025/11/24 13:16:33 by jleiva-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo_bonus.h"

static void	*check_death(void *param)
{
	t_table	*table;

	table = param;
	sem_wait(table->death_sem);
	pthread_mutex_lock(table->mutex);
	table->status = 0;
	pthread_mutex_unlock(table->mutex);
	return (NULL);
}

static void	*check_meals(void *param)
{
	t_table	*table;
	int		i;

	table = param;
	i = -1;
	while (++i < table->nphilos)
		sem_wait(table->meals_sem);
	pthread_mutex_lock(table->mutex);
	table->status = 0;
	pthread_mutex_unlock(table->mutex);
	return (NULL);
}

static void	create_threads(t_table *table)
{
	if (pthread_create(&table->death_checker, NULL, &check_death, table))
	{
		cleanup(table);
		exit(1);
	}
	if (pthread_create(&table->meals_checker, NULL, &check_meals, table))
	{
		sem_post(table->death_sem);
		pthread_join(table->death_checker, NULL);
		cleanup(table);
		exit(1);
	}
}

void	checker(t_table *table)
{
	int	status;
	int	i;

	create_threads(table);
	status = 1;
	while (status)
	{
		pthread_mutex_lock(table->mutex);
		status = table->status;
		pthread_mutex_unlock(table->mutex);
		usleep(500);
	}
	sem_post(table->death_sem);
	i = -1;
	while (++i < table->nphilos)
		sem_post(table->meals_sem);
	pthread_join(table->death_checker, NULL);
	pthread_join(table->meals_checker, NULL);
}
