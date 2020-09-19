
#include "lemin.h"

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

static void go_algo(t_main *map/*, t_main *map2*/)
{
	int rooms_done = 0;
	int linkz = 0;
	special_cases();/////this thing will check and proceed two special cases:
	////1. there's a direct start-end connection 2. there's only one room connected to start
	rooms_done = power_levels(map);
	delete_bad_kids(map->all_links_here, map);
	directions(map->all_links_here);
	count_connections(map->all_links_here);
	delete_worse_kids(map->all_links_here, map);
	create_paths(map);
	lets_go(map);
}


int			main(int ac, char **av)
{
	t_main	*map;
	t_main	*map2;

	if (ac == 2)
	{
		if (!(map = (t_main*)ft_memalloc(sizeof(t_main))))
			return (-1);
		map = parse_input(av, map);
		if (!(map2 = (t_main*)ft_memalloc(sizeof(t_main))))
			return (-1);
		map2 = parse_input(av, map2);
//		printf("kewl!\n");////dlete me later
	}
	go_algo(map/*, map2*/);
//	printf ("not kewl!\n");///delete me later
	return (0);
}
