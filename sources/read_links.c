/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_links.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyuriko <cyuriko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 14:31:30 by cyuriko           #+#    #+#             */
/*   Updated: 2020/03/15 22:03:48 by cyuriko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static t_room	*find_room(t_main *data, char *name)
{
	t_room		*room;

	room = data->all_rooms_here;
	while (room)
	{
		if (ft_strequ(room->name, name))
			return (room);
		room = room->next;
	}
	return (NULL);
}

static t_link	*make_link(char *line, t_link *link, t_main *data)
{
	t_link		*result;
	char		**split;

	if (!(result = (t_link*)ft_memalloc(sizeof(t_link))) ||
			!(split = ft_strsplit(line, '-')))
	{
		ft_strdel(&line);
		return (NULL);
	}
	link->next = result;
	result->prev = link;
	result->first_room = find_room(data, split[0]);
	result->second_room = find_room(data, split[1]);
	del_str_arr(split);
	if (!result->first_room || !result->second_room
	|| duplicate_links(result, data))
	{
		ft_strdel(&line);
		return (NULL);
	}
	print_and_delete(line);
	return (result);
}

static t_link	*initial_link(t_main *data)
{
	t_link		*result;
	char		**split;

	split = NULL;
	if (!(result = (t_link*)ft_memalloc(sizeof(t_link))))
		return (NULL);
	data->all_links_here = result;
	if (!(split = ft_strsplit(data->courier, '-')))
		return (NULL);
	result->first_room = find_room(data, split[0]);
	result->second_room = find_room(data, split[1]);
	del_str_arr(split);
	if (!result->first_room || !result->second_room)
	{
		ft_strdel(&data->courier);
		return (NULL);
	}
	print_and_delete(data->courier);
	return (result);
}

static int		is_command(char *line)
{
	if (ft_strequ(line, "##start") || ft_strequ(line, "##end"))
		return (1);
	return (0);
}

int				read_links(t_main *data)
{
	t_link		*link;
	char		*line;

	if (!(link = initial_link(data)))
		return (0);
	while (get_next_line(data->del_me_fd, &line) > 0)
	{
		if (is_comment(line))
		{
			if (!is_command(line))
			{
				print_and_delete(line);
				continue ;
			}
			break ;
		}
		if (is_link(line))
		{
			if (!(link = make_link(line, link, data)))
				return (0);
			continue;
		}
		break ;
	}
	return (1);
}
