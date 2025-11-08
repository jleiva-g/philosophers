/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleiva-g <jleiva-g@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 17:34:41 by jleiva-g          #+#    #+#             */
/*   Updated: 2025/11/08 04:25:47 by jleiva-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo_bonus.h"

static void	check_death(t_philo *philo)
{
	if (get_time(philo->table->stime) - philo->last_meal <= philo->table->tdie)
	{
		print_status(philo->table, philo->id, 'd');
		sem_post(philo->death_sem);
		exit(1);
	}
}

void	routine(t_philo *philo)
{
	while (1)
	{
		sem_wait(philo->fork_sem);
		check_death(philo);
		print_status(philo->table, philo->id, 'f');
		sem_wait(philo->fork_sem);
		check_death(philo);
		print_status(philo->table, philo->id, 'f');
		philo->last_meal = get_time(philo->table->stime);
		print_status(philo->table, philo->id, 'e');
		usleep(philo->table->teat * 1000);
		if (++philo->meals == philo->table->max_meals)
			sem_post(philo->meals_sem);
		sem_post(philo->fork_sem);
		sem_post(philo->fork_sem);
		check_death(philo);
		print_status(philo->table, philo->id, 's');
		usleep(philo->table->tsleep * 1000);
		check_death(philo);
		print_status(philo->table, philo->id, 't');
	}
}
