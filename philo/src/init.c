/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleiva-g <jleiva-g@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 19:40:45 by jleiva-g          #+#    #+#             */
/*   Updated: 2025/10/28 20:00:59 by jleiva-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	init(t_data *data, int argc, char **argv)
{
	data->nphilos = argv[1];
	data->tdie = ft_atol(argv[2]);
	data->teat = ft_atol(argv[3]);
	data->tsleep = ft_atol(argv[4]);
	if (argc == 6)
		data->must_eat = ft_atol(argv[5]);
}
