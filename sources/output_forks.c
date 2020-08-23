//
// Created by Carly Yuriko on 8/23/20.
//

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
	len = 0;
	while (counter)
	{
		counter = counter->where;
		len++;
	}
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
			path_len = check_path(counter);
			path_len_checker = !path_len_checker ? path_len : path_len_checker;
			path_len_checker = path_len_checker < path_len ? path_len_checker : path_len;
			best = path_len < path_len_checker ? counter : best;
		}
		counter = counter->next;
	}
	return (best);
}

static void delete_other_outputs(t_room *room, t_link *links, t_link *best)
{
	t_link *to_delete;

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
				to_delete->second_room->inputs--;
				to_delete->first_room->outputs--;
				delete_link(to_delete);
			}
			to_delete = to_delete->next;
			continue;
		}
	}
}

void delete_output(t_room *room, t_main *map)
{
	t_link *link_to_save;

	link_to_save = map->all_links_here;
	if (should_delete_output(room, map))
	{
		link_to_save = find_good_output(room, map->all_links_here);
		delete_other_outputs(room, map->all_links_here, link_to_save);
	}
	delete_worse_kids(map->all_links_here);
}