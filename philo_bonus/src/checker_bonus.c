/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleiva-g <jleiva-g@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 17:34:39 by jleiva-g          #+#    #+#             */
/*   Updated: 2025/12/13 11:46:03 by jleiva-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo_bonus.h"

static void	*check_death(void *param)
{
	t_table	*table;

	table = param;
	sem_wait(table->death_sem);
	sem_wait(table->status_sem);
	table->status = 0;
	sem_post(table->status_sem);
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
	sem_wait(table->status_sem);
	table->status = 0;
	sem_post(table->status_sem);
	return (NULL);
}

static void	create_threads(t_table *table)
{
	if (pthread_create(&table->death_checker, NULL, &check_death, table))
	{
		cleanup(table);
		exit(EXIT_FAILURE);
	}
	if (pthread_create(&table->meals_checker, NULL, &check_meals, table))
	{
		sem_post(table->death_sem);
		pthread_join(table->death_checker, NULL);
		cleanup(table);
		exit(EXIT_FAILURE);
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
		sem_wait(table->status_sem);
		status = table->status;
		sem_post(table->status_sem);
		usleep(100);
	}
	sem_post(table->death_sem);
	i = -1;
	while (++i < table->nphilos)
		sem_post(table->meals_sem);
	pthread_join(table->death_checker, NULL);
	pthread_join(table->meals_checker, NULL);
}
