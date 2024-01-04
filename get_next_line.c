/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitelka <aaitelka@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/23 10:02:52 by aaitelka          #+#    #+#             */
/*   Updated: 2024/01/04 15:44:45 by aaitelka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <string.h>

size_t	endl_index(const char *s)
{
	size_t	p;

	p = 0;
	while (s[p])
	{
		if (s[p] == '\n')
			break ;
		p++;
	}
	return (p + 1);
}

char	*read_line(char *buf)
{
	size_t	len;
	char	*line;

	if (!buf)
		return (NULL);
	len = endl_index(buf);
	if (len == 0)
		return (NULL);
	line = (char *) malloc(sizeof(char) * (len + 1));
	line[len] = '\0';
	if (line)
	{
		while (len--)
			line[len] = buf[len];
	}
	return (line);
}

char	*get_next_line(int fd)
{
    static char	*rem;
    char    	*line;
    char		*buf;
    ssize_t		ret;

    line = "";
    buf = (char *) malloc(sizeof(char) * BUFFER_SIZE);
    if (fd < 0 || read(fd, NULL, 0) < 0 || BUFFER_SIZE <= 0)
        return (free(buf), NULL);
    if (rem)
        line = rem;
    ret = read(fd, buf, BUFFER_SIZE);
    while (*buf || *line)
    {
        if ((!ret && !ft_strchr(line, '\n')))
        {
            rem = NULL;
            free(buf);
            break ;
        }
        buf[ret] = '\0';
        if (ft_strchr(buf, '\n'))
            rem = ft_strchr(buf, '\n') + 1;
        else
            rem = ft_strchr(line, '\n') + 1;
        line = join(line, buf);
        if (ft_strchr(line, '\n'))
            break ;
        ret = read(fd, buf, BUFFER_SIZE);
    }
    char *realine = read_line(line);
    free(line);
    return (realine);
}
