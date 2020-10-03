/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyuriko <cyuriko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 21:21:11 by cyuriko           #+#    #+#             */
/*   Updated: 2020/03/11 20:10:22 by cyuriko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

int		is_comment(char *line)
{
	int	len;

	len = 0;
	if (line)
	{
		len = ft_strlen(line);
		if (len > 1)
		{
			if (line[0] == '#')
				return (1);
		}
	}
	return (0);
}

int		is_room(char *line)
{
	if (!line)
		return (0);
	if (split_bits(line, ' ') != 3)
		return (0);
	if (line[0] == 'L')
		return (0);
	return (1);
}

int		is_link(char *line)
{
	if (!line)
		return (0);
	if (split_bits(line, '-') != 2)
		return (0);
	return (1);
}
