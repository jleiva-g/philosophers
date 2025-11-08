/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleiva-g <jleiva-g@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 16:06:25 by jleiva-g          #+#    #+#             */
/*   Updated: 2025/11/08 04:11:32 by jleiva-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo_bonus.h"

int	main(int argc, char **argv)
{
	t_table	table;
	int		i;

	if (argc < 5 || argc > 6)
		return (1);
	init(&table, argc, argv);
	table.stime = get_time(0);
	checker(&table);
	i = -1;
	while (++i < table.nphilos)
		pthread_join(table.threads[i], NULL);
	cleanup(&table);
	return (0);
}
