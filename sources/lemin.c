
#include "lemin.h"

static void count_links_for_each_room(t_main *map)
{
	t_link *counter;

	counter = map->all_links_here;
	while (counter)
	{
		counter->first_room->linkz++;
		counter->second_room->linkz++;

		counter = counter->next;
	}
}

static void recalibrate_link(t_room *source, t_room *destinaton)
{
	destinaton->level = source->level + 1;
}

static bool recalibrate_levels(t_link *counter)
{
	int diff = counter->first_room->level > counter->second_room->level ? counter->first_room->level - counter->second_room->level : counter->second_room->level - counter->first_room->level;
	int workd = false;

	if (diff > 1)
	{
		if (counter->first_room->level > counter->second_room->level && counter->second_room->linkz > 2)
		{
			recalibrate_link(counter->first_room, counter->second_room);
			workd = true;
		}

		else if (counter->second_room->level > counter->first_room->level && counter->first_room->linkz > 2)
		{
			recalibrate_link(counter->second_room, counter->first_room);
			workd = true;
		}

	}
	return (workd);
}


static void set_superposition(t_main *map)
{
	t_link *counter;

	counter = map->all_links_here;
	count_links_for_each_room(map);
	while (counter )
	{
		if (counter->first_room != map->start
		&& counter->second_room != map->start
		&& counter->first_room != map->end
		&& counter->second_room != map->end)
		{
			if (recalibrate_levels(counter))
			{
				counter = map->all_links_here;
				continue ;
			}
		}

		counter = counter->next;
	}

}

static int count_WRoomz_delete_me(t_room *rooomz)
{
	t_room *rroomz;

	rroomz = rooomz;
	int roomz = 0;

	while (rroomz)
	{
		roomz++;
		rroomz = rroomz->next;
	}
	return (roomz);
}

void DEBUG_print_INITIAL(t_main *map)
{
	t_link *counter;
	int end_connections = 0;
	int end_power_lvls = 0;

	counter = map->all_links_here;
	while(counter)
	{
		if (counter->second_room == map->end)
		{
			end_connections++;
			if (counter->first_room == map->end)
			{
				if (counter->second_room->level > 0)
					end_power_lvls++;
			}
			if (counter->second_room == map->end)
			{
				if (counter->first_room->level > 0)
					end_power_lvls++;
			}

		}
		counter = counter->next;
	}
	printf("end connections found: |%d| levels set: |%d|\n", end_connections, end_power_lvls);
}

int count_WLINKZ_delete_me(t_link *linkz)
{
	t_link *linkiz;

	linkiz = linkz;
	int c = 0;
	while (linkiz)
	{
		c++;
		linkiz = linkiz->next;
	}
	return (c);
}

static void special_cases()
{
	return ;
}

static void go_algo(t_main *map)
{

	/*
	 * checkity check
	 * this may be not needed but let it stay for now
	 */
	int rooms_ttl;
	int rooms_done = 0;
	rooms_ttl = count_WRoomz_delete_me(map->all_rooms_here);
	/*
	 * end of checkity check params
	 */
	int linkz = 0;
	special_cases();/////this thing will check and proceed two special cases:
	////1. there's a direct start-end connection 2. there's only one room connected to start
//	if (!power_levels(map))
//		return ;
	rooms_done = power_levels(map);
	DEBUG_print_INITIAL(map);///del me
	delete_bad_kids(map->all_links_here, map);
	DEBUG_print_INITIAL(map);
	linkz = count_WLINKZ_delete_me(map->all_links_here);
	set_superposition(map);
	directions(map->all_links_here);
	count_connections(map->all_links_here);
	delete_worse_kids(map->all_links_here, map);
	DEBUG_print_INITIAL(map);
	linkz = count_WLINKZ_delete_me(map->all_links_here);
	create_paths(map);
	lets_go(map);
}


int			main(int ac, char **av)
{
	t_main	*map;

	if (ac == 2)
	{
		if (!(map = (t_main*)ft_memalloc(sizeof(t_main))))
			return (-1);
		map = parse_input(av, map);
		printf("kewl!\n");////dlete me later
	}
	go_algo(map);
	printf ("not kewl!\n");///delete me later
	return (0);
}
