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

static void build_paths()
{
	printf("haha\n");///////
}

void 	create_paths(t_main *map)
{
	delete_input_forks(map);
	delete_output_forks(map);
	build_paths();
}
