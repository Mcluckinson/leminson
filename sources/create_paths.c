//
// Created by Carly Yuriko on 8/23/20.
//

#include "lemin.h"

static void delete_input_forks(t_main *map)
{
	t_room *counter;

	counter = map->all_rooms_here;
	while(counter)
	{
		delete_input(counter, map);
		counter = counter->next;
	}
}

static void delete_output_forks(t_main *map)
{
	t_room *counter;

	counter = map->all_rooms_here;
	while(counter)
	{
		delete_output(counter, map);
		counter = counter->next;
	}
}

static void build_paths()
{

}

void 	create_paths()
{
	delete_input_forks();
	delete_output_forks();
	build_paths();
}
