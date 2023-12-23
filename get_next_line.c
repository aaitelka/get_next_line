/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitelka <aaitelka@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/23 10:02:52 by aaitelka          #+#    #+#             */
/*   Updated: 2023/12/23 11:29:40 by aaitelka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

char	*get_next_line(int fd)
{
	static char	*line;
	char		*buffer;
	size_t		endl_p;
	
	buffer = malloc(BUFFER_SIZE);
	int i = 0;
	while (read(fd, buffer, BUFFER_SIZE))
	{
		endl_p = endl(buffer);
		line = malloc(endl_p);
		
		if (endl_p)
		{	
			while (buffer[i] && endl_p--)
			{
				line[i] = buffer[i];
				i++;	
			}
			line[i] = '\0';
		}
	}
	return (line);
}