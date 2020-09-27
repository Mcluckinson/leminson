/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_directions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyuriko <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/20 15:58:24 by cyuriko           #+#    #+#             */
/*   Updated: 2020/09/20 15:58:26 by cyuriko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

/*
** this will change rooms links so first room lvl is always <= second room lvl
*/

static void		fix_link(t_link *link)
{
	t_room *buff;

	buff = NULL;
	if (!link)
		return ;
	if (link->first_room->level > link->second_room->level)
	{
		buff = link->first_room;
		link->first_room = link->second_room;
		link->second_room = buff;
	}
}

void			directions(t_link *links)
{
	t_link *counter;

	counter = links;
	while (counter)
	{
		fix_link(counter);
		counter = counter->next;
	}
}
