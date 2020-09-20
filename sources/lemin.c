/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyuriko <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/20 15:58:58 by cyuriko           #+#    #+#             */
/*   Updated: 2020/09/20 15:59:00 by cyuriko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

int count_links(t_link *linkz)
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

static void go_algo(t_main *map1, t_main *map2)
{
	t_main *map_final;

	map_final = NULL;
	start_end_link(map1);
	map_final = run_algo(map1, map2);
	lets_go(map_final);
}

/*static bool check_args(int ac, char **av)
{
	int i;

	i = 1;
	if (ac == 2)
	{
		if (ft_strequ(av[1], "-h"))
		{
			ft_error("usage: ./lem-in < map or simply ./lem-in; same"
			"with -r for nice report on results");
			return (false);
		}
		else if (ft_strequ(av[1], "-r"))
			return (true);
		else
			ft_error("this is not the way, try ./lem-in -h for usage");
	}
	else if (ac > 2)
		ft_error("this is not the way, try ./lem-in -h for usage");
	return (false);
}*/

int			main(int ac, char **av)
{
	t_main	*map1;
	t_main	*map2;
//	bool	report;
	ac = 2;
//	report = check_args(ac, av); DO NOT DELETE! UNCOMMENT WHEN ALL IS DONE
	if (!(map1 = (t_main*)ft_memalloc(sizeof(t_main))))
		return (-1);
	if (!(map2 = (t_main*)ft_memalloc(sizeof(t_main))))
		return (-1);
	map1 = parse_input(av, map1);
	map2 = parse_input(av, map2);
//	map1->report = report;
//	map2->report = report;
	go_algo(map1, map2);
	exit(0);
}
