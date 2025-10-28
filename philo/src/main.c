/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleiva-g <jleiva-g@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 16:06:25 by jleiva-g          #+#    #+#             */
/*   Updated: 2025/10/28 19:18:16 by jleiva-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	main(int argc, char **argv)
{
	int				i;
	long			time;

	(void) argc;
	(void) argv;
	i = 10;
	time = get_time(0);
	while (i--)
	{
		usleep(1000000);
		printf("%08li\n", get_time(time));
	}
	return (0);
}
