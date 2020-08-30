
#include "lemin.h"

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
	delete_bad_kids(map->all_links_here, map);
	linkz = count_WLINKZ_delete_me(map->all_links_here);
	directions(map->all_links_here);
	count_connections(map->all_links_here);
	delete_worse_kids(map->all_links_here, map);
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
