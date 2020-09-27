/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freeshing.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyuriko <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/20 15:58:35 by cyuriko           #+#    #+#             */
/*   Updated: 2020/09/20 15:58:37 by cyuriko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static void		free_links(t_link *links)
{
	if (!links)
		return ;
	free_links(links->next);
	free(links);
}

void			free_map(t_main *map)
{
	if (map)
	{
		free_rooms(map->all_rooms_here);
		free_links(map->all_links_here);
		free(map);
	}
}

void			free_rooms(t_room *room)
{
	if (!room)
		return ;
	free_rooms(room->next);
	if (room->name)
		free(room->name);
	free(room);
}
