/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_rooms.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyuriko <cyuriko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 21:39:52 by cyuriko           #+#    #+#             */
/*   Updated: 2020/03/15 21:26:20 by cyuriko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

int				valid_coords(t_room *room, t_room *list)
{
	t_room	*start;

	start = list;
	while (start && start->next)
	{
		if (start->x == room->x)
		{
			if (start->y == room->y)
				return (0);
		}
		if (ft_strequ(start->name, room->name))
			return (0);
		start = start->next;
	}
	return (1);
}

static t_room	*make_room(t_room *room, char *line, t_main *data)
{
	t_room	*result;
	char	**room_data;

	if (!(result = (t_room*)ft_memalloc(sizeof(t_room))))
		ft_error("malloc failed");
	if (room)
		room->next = result;
	if (!(room_data = ft_strsplit(line, ' ')))
	{
		free(result);
		ft_error("malloc failed");
	}
	result->name = ft_strdup(room_data[0]);
	result->x = ft_atoi(room_data[1]);
	result->y = ft_atoi(room_data[2]);
	del_str_arr(room_data);
	if (!data->all_rooms_here)
		data->all_rooms_here = result;
	print_and_delete(line);
	return (result);
}

static int		start_end_check(char *line, t_room **rooms, t_main *data)
{
	int	flag;

	flag = 0;
	flag += (ft_strequ(line, "##start") ? 1 : 0);
	flag += (ft_strequ(line, "##end") ? 2 : 0);
	if (flag != 1 && flag != 2)
		return (print_and_delete(line));
	print_and_delete(line);
	if ((get_next_line(data->del_me_fd, &line) < 1) || !(is_room(line)))
		return (del_line_and_return(line, 0));
	if (flag == 1 && !data->start)
	{
		if (!(*rooms = make_room(*rooms, line, data)))
			return (del_line_and_return(line, 0));
		data->start = *rooms;
		return (1);
	}
	else if (flag == 2 && !data->end)
	{
		if (!(*rooms = make_room(*rooms, line, data)))
			return (del_line_and_return(line, 0));
		data->end = *rooms;
		return (1);
	}
	return (del_line_and_return(line, 0));
}

static int		transfer_line(t_main *main, char *line)
{
	main->courier = line;
	return (1);
}

int				read_rooms(t_main *data)
{
	char	*line;
	t_room	*rooms;

	rooms = NULL;
	while (get_next_line(data->del_me_fd, &line) > 0)
	{
		if (is_comment(line))
		{
			if (!start_end_check(line, &rooms, data))
				return (0);
			continue ;
		}
		if (is_room(line))
		{
			rooms = make_room(rooms, line, data);
			if (valid_coords(rooms, data->all_rooms_here))
				continue ;
			line = NULL;
		}
		if (is_link(line))
			return (transfer_line(data, line));
		break ;
	}
	return (line ? del_line_and_return(line, 0) : 0);
}
