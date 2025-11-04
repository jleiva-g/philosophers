/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleiva-g <jleiva-g@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 17:34:41 by jleiva-g          #+#    #+#             */
/*   Updated: 2025/11/04 01:39:22 by jleiva-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static int	get_status(t_table *table)
{
	int	status;

	pthread_mutex_lock(&table->smutex);
	status = table->status;
	pthread_mutex_unlock(&table->smutex);
	return (status);
}

static int	take_fork(t_philo *philo, int side)
{
	t_fork	*fork;

	if (side)
		fork = philo->left_fork;
	else
		fork = philo->right_fork;
	pthread_mutex_lock(&fork->mutex);
	if (fork->is_taken)
	{
		pthread_mutex_unlock(&fork->mutex);
		return (1);
	}
	else
	{
		pthread_mutex_unlock(&fork->mutex);
		fork->is_taken = 1;
		print_status(philo->table, philo->id, 'f');
		return (0);
	}
}

static void	ph_eat(t_philo *philo)
{
	print_status(philo->table, philo->id, 'e');
	pthread_mutex_lock(&philo->lmutex);
	philo->last_meal = get_time(philo->table->stime);
	pthread_mutex_unlock(&philo->lmutex);
	usleep(philo->table->teat * 1000);
	pthread_mutex_lock(&philo->mmutex);
	philo->meals++;
	pthread_mutex_unlock(&philo->mmutex);
	pthread_mutex_lock(&philo->left_fork->mutex);
	philo->left_fork->is_taken = 0;
	pthread_mutex_unlock(&philo->left_fork->mutex);
	pthread_mutex_lock(&philo->right_fork->mutex);
	philo->right_fork->is_taken = 0;
	pthread_mutex_unlock(&philo->right_fork->mutex);
}

static void	ph_sleep(t_philo *philo)
{
	print_status(philo->table, philo->id, 's');
	usleep(philo->table->tsleep * 1000);
}

void	*routine(void *param)
{
	t_philo	*philo;

	philo = (t_philo *) param;
	if (!(philo->id % 2))
	{
		print_status(philo->table, philo->id, 't');
		usleep(500);
	}
	while (!get_status(philo->table))
	{
		while (take_fork(philo, philo->table->nphilos != philo->id))
			if (get_status(philo->table))
				return (NULL);
		while (take_fork(philo, philo->table->nphilos == philo->id))
			if (get_status(philo->table))
				return (NULL);
		ph_eat(philo);
		if (get_status(philo->table))
			return (NULL);
		ph_sleep(philo);
		if (get_status(philo->table))
			return (NULL);
		print_status(philo->table, philo->id, 't');
	}
	return (NULL);
}
