/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_all_paths.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyuriko <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/27 19:11:51 by cyuriko           #+#    #+#             */
/*   Updated: 2020/09/27 19:11:55 by cyuriko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static void		invalid_path(t_path *path)
{
	if (!path)
		return ;
	clear_path(path);
	free(path);
	path = NULL;
}

static t_path	*country_roads(t_room *room, t_main *map)
{
	t_path *path;
	t_room *room_iterator;
	t_link *link_iterator;

	if (!(path = (t_path*)ft_memalloc(sizeof(t_path))))
		ft_error("malloc failed");
	room_iterator = room;
	path->current = room_iterator;
	link_iterator = map->all_links_here;
	while (link_iterator)
	{
		link_iterator = map->all_links_here;
		while (link_iterator && link_iterator->first_room != room_iterator)
			link_iterator = link_iterator->next;
		if (!link_iterator)
		{
			invalid_path(path);
			return (NULL);
		}
		room_iterator->where = link_iterator->second_room;
		room_iterator = room_iterator->where;
		if (room_iterator == map->end)
			return (path);
	}
	return (path);
}

void			build_all_paths(t_main *map)
{
	t_link *link_iterator;
	t_path *paths;

	paths = NULL;
	link_iterator = map->all_links_here;
	while (link_iterator)
	{
		if (link_iterator->first_room->level == 1
			&& !link_iterator->first_room->where)
		{
			if (!map->paths)
			{
				paths = country_roads(link_iterator->first_room, map);
				if (paths)
					map->paths = paths;
				else
					link_iterator->first_room->level = -1;
			}
			else
			{
				paths->next = country_roads(link_iterator->first_room, map);
				if (paths->next)
					paths = paths->next;
				else
					link_iterator->first_room->level = -1;
			}
		}
		link_iterator = link_iterator->next;
	}
}
