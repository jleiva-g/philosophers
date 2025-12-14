/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleiva-g <jleiva-g@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 17:34:41 by jleiva-g          #+#    #+#             */
/*   Updated: 2025/12/14 17:35:35 by jleiva-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo_bonus.h"

static void	check_termination(t_philo *philo)
{
	int	status;

	sem_wait(philo->philo_sem);
	status = philo->table->status;
	sem_post(philo->philo_sem);
	if (!status)
	{
		pthread_join(philo->death_checker, NULL);
		pthread_join(philo->sigterm_checker, NULL);
		child_cleanup(philo, EXIT_SUCCESS);
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
		usleep(philo->table->tsleep * 1000 + 1000);
		check_termination(philo);
		print_status(philo->table, philo->id, 't');
	}
}

static void	*check_death(void *param)
{
	t_philo	*philo;
	int		status;

	philo = param;
	status = 1;
	while (status)
	{
		if (get_time(philo->table->stime) - philo->last_meal
			> philo->table->tdie)
		{
			sem_post(philo->table->death_sem);
			print_status(philo->table, philo->id, 'd');
			sem_wait(philo->philo_sem);
			philo->table->status = 0;
			sem_post(philo->philo_sem);
			sem_post(philo->table->plate_sem);
			sem_post(philo->table->forks_sem);
		}
		sem_wait(philo->philo_sem);
		status = philo->table->status;
		sem_post(philo->philo_sem);
		usleep(500);
	}
	return (NULL);
}

static void	*check_sigterm(void *param)
{
	t_philo	*philo;

	philo = param;
	sem_wait(philo->table->sigterm_sem);
	sem_wait(philo->philo_sem);
	philo->table->status = 0;
	sem_post(philo->philo_sem);
	return (NULL);
}

void	start_routine(t_philo *philo)
{
	sem_unlink(philo->sem_name);
	philo->philo_sem = sem_open(philo->sem_name, O_CREAT, 0644, 1);
	if (philo->philo_sem == SEM_FAILED)
	{
		sem_post(philo->table->death_sem);
		child_cleanup(philo, EXIT_FAILURE);
	}
	if (pthread_create(&philo->death_checker, NULL, &check_death, philo))
	{
		sem_post(philo->table->death_sem);
		child_cleanup(philo, EXIT_FAILURE);
	}
	if (pthread_create(&philo->sigterm_checker, NULL, &check_sigterm, philo))
	{
		sem_post(philo->table->death_sem);
		sem_wait(philo->philo_sem);
		philo->table->status = 0;
		sem_post(philo->philo_sem);
		pthread_join(philo->death_checker, NULL);
		child_cleanup(philo, EXIT_FAILURE);
	}
	routine(philo);
}
