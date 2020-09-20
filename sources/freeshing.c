/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freeshing.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyuriko <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/20 15:58:35 by cyuriko           #+#    #+#             */
/*   Updated: 2020/09/20 15:58:37 by cyuriko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "lemin.h"

/*
 * потом добавить чистку комнат и муравьев, тк если все збс при считывании, то
 * нужно будет все фришить в конце программы
 */

void		free_map(t_main *map)
{
	if (map)
		free(map);
}

void		free_rooms(t_room *room)
{
	if (!room)
		return ;
	while(room->next)
		free_rooms(room->next);////////а room?
	if (room->name)
		free(room->name);
	free(room);
}
