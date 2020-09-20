/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyuriko <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/20 15:57:18 by cyuriko           #+#    #+#             */
/*   Updated: 2020/09/20 15:57:20 by cyuriko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//
// Created by Carly Yuriko on 8/23/20.
//

#include "lemin.h"

void clear_path(t_path *path)
{
	t_room *counter;
	t_room *prev;

	prev = path->current;
	counter = prev->where;

	while (counter)
	{
		prev->where = NULL;
		prev = counter;
		counter = counter->where;
	}
}

t_path *build_path_with_link(t_room *room, t_link *link, t_main *map)
{
	t_path *path;
	t_room *curr;
	t_link *link_counter;

	curr = room;
	path = (t_path*)ft_memalloc(sizeof(t_path));
		////protec
	path->current = curr;
	link_counter = link;
	curr->where = link_counter->second_room;
	link_counter = map->all_links_here;
	while (link_counter)
	{
		if (curr->where == map->end)
			return (path);/////leak?
		if (link_counter->first_room == curr->where)
		{
			curr = curr->where;
			curr->where = link_counter->second_room;
			link_counter = map->all_links_here;
		}
		link_counter = link_counter->next;
	}
	clear_path(path);
	free(path);
	return (NULL);
}
