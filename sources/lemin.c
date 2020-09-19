
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

static void go_algo(t_main *map1, t_main *map2)
{
	t_main *map_final;

	map_final = NULL;
	special_cases();/////this thing will check and proceed two special cases:
	////1. there's a direct start-end connection 2. there's only one room connected to start

	map_final = run_algo(map1, map2);
	/*int rooms_done = 0;
	int linkz = 0;
	special_cases();/////this thing will check and proceed two special cases:
	////1. there's a direct start-end connection 2. there's only one room connected to start
	rooms_done = power_levels(map);
	delete_bad_kids(map->all_links_here, map);
	directions(map->all_links_here);
	count_connections(map->all_links_here);
	delete_worse_kids(map->all_links_here, map);
	create_paths(map);*/
	lets_go(map_final);
}

static void check_args(int ac, char **av)
{
	////////THIS IS NOT the ACTUAL FUnCtiON
	////DEW IT tHO
	if (ac > 1)
		printf("many args");
	if (av)
		printf("has args");
}

int			main(int ac, char **av)
{
	t_main	*map1;
	t_main	*map2;

	check_args(ac, av);
	if (!(map1 = (t_main*)ft_memalloc(sizeof(t_main))))
		return (-1);
	map1 = parse_input(av, map1);
	if (!(map2 = (t_main*)ft_memalloc(sizeof(t_main))))
		return (-1);
	map2 = parse_input(av, map2);
	go_algo(map1, map2);
	return (0);
}
