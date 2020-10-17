/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_and_filling.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyuriko <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/20 15:59:22 by cyuriko           #+#    #+#             */
/*   Updated: 2020/09/20 15:59:24 by cyuriko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

t_main			*ant_colony_creation(int quant, t_main *map)
{
	int		i;
	t_ant	*ant;

	i = -1;
	while (++i < quant)
	{
		if (!i)
		{
			if (!(ant = (t_ant*)ft_memalloc(sizeof(t_ant))))
				ft_error("ANTS FAILED to ALLOC");
			map->first_ant = ant;
		}
		ant->num = quant - i;
		ant->curr_room = map->start;
		if ((i + 1) == quant)
			return (map);
		if (!(ant->next = (t_ant*)ft_memalloc(sizeof(t_ant))))
			ft_error("ANTS FAILED to ALLOC");
		ant = ant->next;
	}
	return (NULL);
}

static int		read_data(t_main *data)
{
	if (!read_ants(data))
		return (0);
	if (!read_rooms(data))
		return (0);
	if (!data->start || !data->end)
		return (0);
	if (!read_links(data))
		return (0);
	return (1);
}

t_main			*structure_filling(t_main *map)
{
	if (!read_data(map))
	{
		free_map(map);
		ft_error("CHTO TO POSHLO NE TAK LOL");
	}
	ant_colony_creation(map->ants, map);
	return (map);
}

t_main			*parse_input(t_main *map)
{
	map = structure_filling(map);
	map->original_ants = map->ants;
	return (map);
}
