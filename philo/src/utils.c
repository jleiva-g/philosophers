/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleiva-g <jleiva-g@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 10:33:04 by jleiva-g          #+#    #+#             */
/*   Updated: 2025/10/28 19:58:12 by jleiva-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

long	get_time(long time)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000 - time);
}

long	ft_atol(char *nptr)
{
	long	n;

	n = 0;
	while (*nptr)
	{
		n = n * 10 + *nptr - '0';
		nptr++;
	}
	return (n);
}
