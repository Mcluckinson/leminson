
#include "lemin.h"

static void special_cases()
{
	return ;
}

static void go_algo(t_main *map)
{
	special_cases();/////this thing will check and proceed two special cases:
	////1. there's a direct start-end connection 2. there's only one room connected to start
	if (!power_levels(map))
		return ;
	delete_bad_kids(map->all_links_here);
	directions(map->all_links_here);
	count_connections(map->all_links_here);
	delete_worse_kids(map->all_links_here);
	create_paths(map);
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
