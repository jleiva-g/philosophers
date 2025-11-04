/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleiva-g <jleiva-g@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 16:06:25 by jleiva-g          #+#    #+#             */
/*   Updated: 2025/11/04 01:03:51 by jleiva-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	main(int argc, char **argv)
{
	t_table	table;
	int		i;

	if (argc < 4 || argc > 5)
		return (1);
	if (init(&table, argc, argv))
		return (1);
	table.stime = get_time(0);
	i = -1;
	while (++i < table.nphilos)
		pthread_create(&table.threads[i], NULL, &routine, &table.philos[i]);
	checker(&table);
	i = -1;
	while (++i < table.nphilos)
		pthread_join(table.threads[i], NULL);
	return (0);
}
