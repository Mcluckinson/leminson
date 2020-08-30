//
// Created by Carly Yuriko on 8/23/20.
//

#include "lemin.h"

static void delete_input_forks(t_main *map)
{
	t_room *counter;/////////this iterates randomly at the moment; fix this so it goes in ascencion according to lvls ITS VITAL
	int lvl;

	lvl = 1;

	while (lvl <= map->max_lvl)
	{
		counter = map->all_rooms_here;
		while(counter)
		{
			if (counter->level == lvl)
				delete_input(counter, map);
			counter = counter->next;
		}
		lvl++;
	}

}

static void delete_output_forks(t_main *map)
{
	t_room *counter;
	int lvl;

	lvl = map->max_lvl;
	while (lvl > 0)
	{
		counter = map->all_rooms_here;
		while(counter)
		{
			if (counter->level == lvl)
				delete_output(counter, map);
			counter = counter->next;
		}
		lvl--;
	}
}

static void invalid_path_CHECK_ME_GOOD(t_main *map, t_path *path)
{
	clear_path(path);
	free(path);
	path = NULL;
}

static t_path *country_roads(t_room *room, t_main *map)
{
	/////build a single path starting with a specific room;
	t_path *path;
	t_room *room_iterator;
	t_link *link_iterator;

	path = (t_path*)ft_memalloc(sizeof(t_path));
		////protect this;
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
			invalid_path_CHECK_ME_GOOD(map, path);
			return (NULL);
		}
		//	ft_error("INVALID SHIT FOUND");/////deal with this correctly;
		room_iterator->where = link_iterator->second_room;
		room_iterator = room_iterator->where;
		if (room_iterator == map->end)
			return (path);

	}
	return (path);
}

static void build_all_paths(t_main *map)
{
	t_link *link_iterator;
	t_path *paths;

	paths = NULL;
	link_iterator = map->all_links_here;
	while (link_iterator)
	{
		if (link_iterator->first_room->level == 1 && !link_iterator->first_room->where)
		{

			if (!map->paths)
			{
				paths = country_roads(link_iterator->first_room, map);///check for null kek
				if (paths)
					map->paths = paths;
				else
					link_iterator->first_room->level = -1;
			}
			else
			{
				paths->next = country_roads(link_iterator->first_room, map);///check for null kek
				if (paths->next)
					paths = paths->next;/////THIS IS BAD, MAKE A PROPER PATH ADDER
				else
					link_iterator->first_room->level = -1;
			}
		}
		link_iterator = link_iterator->next;
	}
}

static void build_paths(t_main *map)
{
	build_all_paths(map);
	count_steps(map);
	if (!(map->path_array = make_path_array(map)))
		ft_error("ERROR! CAN'T MALLOC STRUCTURE");
}

void 	create_paths(t_main *map)
{
//	int LINkz = 0;

	delete_input_forks(map);
//	LINkz = count_WLINKZ_delete_me(map->all_links_here);
	delete_output_forks(map);
//	LINkz = count_WLINKZ_delete_me(map->all_links_here);;
	build_paths(map);
}
