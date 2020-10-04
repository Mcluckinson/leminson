/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   more_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyuriko <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/04 14:54:07 by cyuriko           #+#    #+#             */
/*   Updated: 2020/10/04 14:54:10 by cyuriko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

int			split_bits(char *line, char c)
{
	char	**split;
	int		i;
	int		j;

	i = -1;
	j = -1;
	split = NULL;
	if (!(split = ft_strsplit(line, c)))
		return (0);
	while (split[++i])
		continue ;
	while (split[++j])
		ft_strdel(&split[j]);
	free(split);
	return (i);
}

void		del_str_arr(char **to_delete)
{
	int		i;

	i = -1;
	if (to_delete)
	{
		while (to_delete[++i])
			ft_strdel(&to_delete[i]);
		free(to_delete);
	}
}

void		clear_reading_stuff(int fd)
{
	char *line;

	while (get_next_line(fd, &line) > 0)
	{
		if (line)
			free(line);
	}
}

int			duplicate_links(t_link *link, t_main *data)
{
	t_link		*start;

	start = data->all_links_here;
	while (start != link && start)
	{
		if ((start->first_room == link->first_room
		&& start->second_room == link->second_room)
		|| (start->first_room == link->second_room
		&& start->second_room == link->first_room)
		|| (start->first_room == start->second_room
		|| link->first_room == link->second_room))
			return (1);
		start = start->next;
	}
	return (0);
}

bool		should_delete(t_room *room, t_main *map)
{
	if (room == map->start || room == map->end)
		return (false);
	if (room->inputs < 2)
		return (false);
	return (true);
}
