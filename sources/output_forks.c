/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output_forks.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyuriko <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/20 15:59:14 by cyuriko           #+#    #+#             */
/*   Updated: 2020/09/20 15:59:16 by cyuriko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static bool should_delete_output(t_room *room, t_main *map)
{
	if (room == map->end || room == map->start)
		return (false);
	if (room->outputs < 2)
		return (false);
	return (true);
}

static int check_path(t_room *room, t_link *link, t_main *map)
{
	int len;
	t_path *path;
	t_room *counter;

	path = build_path_with_link(room, link, map);
	if (!path)
		return (0);
	counter = path->current;
	len = 0;
	while (counter)
	{
		counter = counter->where;
		len++;
	}
	clear_path(path);
	free(path);
	path = NULL;
	return (len);
}

static t_link *find_good_output(t_room *room, t_main *map)
{
	t_link *best;
	t_link *counter;
	int path_len;
	int path_len_checker;

	path_len_checker = 0;
	counter = map->all_links_here;
	best = NULL;
	while (counter)
	{
		if (counter->first_room == room)
		{
			path_len = check_path(room, counter, map);
			path_len_checker = !path_len_checker ? path_len : path_len_checker;
			path_len_checker = path_len_checker < path_len ? path_len_checker : path_len;
			best = (path_len && path_len <= path_len_checker) ? counter : best;
		}
		counter = counter->next;
	}
	return (best);
}

static void delete_other_outputs(t_room *room, t_link *links, t_link *best, t_main *map)
{
	t_link *to_delete;
	t_link *to_delete_buff;

	to_delete = links;
	while (to_delete)
	{
		if (to_delete->first_room == room)
		{
			if (to_delete == best)
			{
				to_delete = to_delete->next;
				continue;
			}
			else
			{
				to_delete_buff = to_delete->next;
				delete_link(to_delete, map);
				to_delete = to_delete_buff;
			}
			continue;
		}
		to_delete = to_delete->next;
	}
}

void delete_output(t_room *room, t_main *map)
{
	t_link *link_to_save;

	link_to_save = map->all_links_here;
	if (should_delete_output(room, map))
	{
		link_to_save = find_good_output(room, map);
		delete_other_outputs(room, map->all_links_here, link_to_save, map);
	}
	delete_worse_kids(map);
}
