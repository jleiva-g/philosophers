/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleiva-g <jleiva-g@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 17:34:41 by jleiva-g          #+#    #+#             */
/*   Updated: 2025/11/24 13:15:40 by jleiva-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static int	get_status(t_table *table)
{
	int	status;

	pthread_mutex_lock(table->smutex);
	status = table->status;
	pthread_mutex_unlock(table->smutex);
	return (status);
}

static int	take_fork(t_philo *philo, int side)
{
	t_fork	*fork;

	if (get_status(philo->table))
		return (0);
	if (side)
		fork = philo->left_fork;
	else
		fork = philo->right_fork;
	pthread_mutex_lock(fork->mutex);
	if (fork->is_taken)
	{
		pthread_mutex_unlock(fork->mutex);
		usleep(10);
		return (1);
	}
	else
	{
		fork->is_taken = 1;
		pthread_mutex_unlock(fork->mutex);
		print_status(philo->table, philo->id, 'f');
		return (0);
	}
}

static int	ph_eat(t_philo *philo)
{
	long	time;

	pthread_mutex_lock(philo->lmutex);
	time = get_time(philo->table->stime);
	if (time - philo->last_meal <= philo->table->tdie)
		philo->last_meal = time;
	else
	{
		pthread_mutex_unlock(philo->lmutex);
		return (1);
	}
	pthread_mutex_unlock(philo->lmutex);
	print_status(philo->table, philo->id, 'e');
	usleep(philo->table->teat * 1000);
	pthread_mutex_lock(philo->mmutex);
	if (philo->meals > -1)
		philo->meals++;
	pthread_mutex_unlock(philo->mmutex);
	pthread_mutex_lock(philo->left_fork->mutex);
	philo->left_fork->is_taken = 0;
	pthread_mutex_unlock(philo->left_fork->mutex);
	pthread_mutex_lock(philo->right_fork->mutex);
	philo->right_fork->is_taken = 0;
	pthread_mutex_unlock(philo->right_fork->mutex);
	return (0);
}

static void	start_thinking(t_philo *philo)
{
	print_status(philo->table, philo->id, 't');
	usleep(1000);
}

void	*routine(void *param)
{
	t_philo	*philo;

	philo = param;
	if (philo->id % 2)
		start_thinking(philo);
	while (!get_status(philo->table))
	{
		while (take_fork(philo, 1))
			;
		while (take_fork(philo, 0))
			;
		if (get_status(philo->table))
			return (NULL);
		if (ph_eat(philo) || get_status(philo->table))
			return (NULL);
		print_status(philo->table, philo->id, 's');
		usleep(philo->table->tsleep * 1000);
		if (get_status(philo->table))
			return (NULL);
		print_status(philo->table, philo->id, 't');
	}
	return (NULL);
}
