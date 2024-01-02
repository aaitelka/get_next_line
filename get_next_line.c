/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitelka <aaitelka@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/23 10:02:52 by aaitelka          #+#    #+#             */
/*   Updated: 2024/01/02 10:36:49 by aaitelka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

char *get_next_line(int fd)
{
	static char *rem;
	char *line = "";
 	int hasendl = 0;
	char *buf = (char *)malloc(sizeof(char) * BUFFER_SIZE);

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, NULL, 0) < 0)
		return (free(buf), NULL);
	int ret;
	if (rem)
		line = join(rem, buf);
	while ((ret = read(fd, buf, BUFFER_SIZE)) > 0 || *rem)
	{
		
		line = join(line, buf);
		
		if (ft_strchr(buf, 10))
			rem = ft_strchr(buf, 10) + 1;
		int i = 0;
		// int position = endl_p(line);
 		while (*line && ft_strchr(line, 10))
		{
			if (line[i] == 10)
			{
				line[i + 1] = '\0'; // add null terminator after endl.
				hasendl = 1;
				break;	
			}
			i++;
		}
		if (hasendl)
			break;
	}
	free(buf);
	return (line);
}
