/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleiva-g <jleiva-g@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 17:34:41 by jleiva-g          #+#    #+#             */
/*   Updated: 2025/11/13 18:47:05 by jleiva-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo_bonus.h"

static void	check_termination(t_philo *philo)
{
	int	status;

	pthread_mutex_lock(philo->table->mutex);
	status = philo->table->status;
	pthread_mutex_unlock(philo->table->mutex);
	if (!status)
	{
		pthread_join(philo->death_checker, NULL);
		pthread_join(philo->sigterm_checker, NULL);
		child_cleanup(philo->table);
		exit(0);
	}
}

static void	routine(t_philo *philo)
{
	while (1)
	{
		sem_wait(philo->table->plate_sem);
		sem_wait(philo->table->forks_sem);
		check_termination(philo);
		print_status(philo->table, philo->id, 'f');
		sem_wait(philo->table->forks_sem);
		check_termination(philo);
		print_status(philo->table, philo->id, 'f');
		philo->last_meal = get_time(philo->table->stime);
		print_status(philo->table, philo->id, 'e');
		usleep(philo->table->teat * 1000);
		if (++philo->meals == philo->table->max_meals)
			sem_post(philo->table->meals_sem);
		sem_post(philo->table->forks_sem);
		sem_post(philo->table->forks_sem);
		sem_post(philo->table->plate_sem);
		check_termination(philo);
		print_status(philo->table, philo->id, 's');
		usleep(philo->table->tsleep * 1000);
		check_termination(philo);
		print_status(philo->table, philo->id, 't');
	}
}

static void	*check_death(void *param)
{
	t_philo	*philo;
	int		status;

	philo = (t_philo *) param;
	status = 1;
	while (status)
	{
		if (get_time(philo->table->stime) - philo->last_meal
			> philo->table->tdie)
		{
			print_status(philo->table, philo->id, 'd');
			pthread_mutex_lock(philo->table->mutex);
			philo->table->status = 0;
			pthread_mutex_unlock(philo->table->mutex);
		}
		pthread_mutex_lock(philo->table->mutex);
		status = philo->table->status;
		pthread_mutex_unlock(philo->table->mutex);
		usleep(1000);
	}
	return (NULL);
}

static void	*check_sigterm(void *param)
{
	t_table	*table;

	table = (t_table *) param;
	sem_wait(table->sigterm_sem);
	pthread_mutex_lock(table->mutex);
	table->status = 0;
	pthread_mutex_unlock(table->mutex);
	return (NULL);
}

void	start_routine(t_philo *philo)
{
	if (pthread_create(&philo->death_checker, NULL, &check_death, philo))
	{
		sem_post(philo->table->death_sem);
		child_cleanup(philo->table);
		exit(1);
	}
	if (pthread_create(&philo->sigterm_checker, NULL, &check_sigterm,
			philo->table))
	{
		sem_post(philo->table->death_sem);
		pthread_mutex_lock(philo->table->mutex);
		philo->table->status = 0;
		pthread_mutex_unlock(philo->table->mutex);
		pthread_join(philo->death_checker, NULL);
		child_cleanup(philo->table);
		exit(1);
	}
	if (!(philo->id % 2))
	{
		print_status(philo->table, philo->id, 't');
		usleep(500);
	}
	routine(philo);
}
