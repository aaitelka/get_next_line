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


size_t endl_index(char *s)
{
    size_t i;

    if (!s)
        return (0);
    i = 0;
    while (s[i])
        if (s[i++] == '\n')
            break ;
    return (i);
}

char *new_rem(char *rem)
{
    char *new_rem;
    size_t len;
    size_t i;

    if (!rem)
        return (NULL);
    i = -1;
    rem = strchr(rem, 10) + 1;
    len = endl_index(rem);
    if (!len)
        return (NULL);
    new_rem = (char *) malloc(len + 1);
    if (!new_rem)
        return (NULL);
    while (len-- && i++)
        new_rem[i] = rem[i];
    return (new_rem);
}

char *read_line(char *buf) {
    size_t len;
    char *line;

    if (!buf || *buf == '\0')
        return (NULL);
    len = endl_index(buf);
    if (!len)
        return (NULL);
    line = (char *) malloc(len + 1);
    if (!line)
        return (NULL);
    line[len] = '\0';
    while (len--)
        line[len] = buf[len];
    free(buf);
    return (line);
}

char	*read_file(int fd, char *res)
{
    char	*buffer;
    int		byte_read;

    buffer = malloc(BUFFER_SIZE + 1);
    if (!buffer)
        return (NULL);
    while ((byte_read = read(fd, buffer, BUFFER_SIZE)) > 0)
    {
        if (byte_read == -1)
            return (NULL);
        buffer[byte_read] = 0;
        res = join(res, buffer);
        if (ft_strchr(buffer, '\n') || !byte_read)
            return (res);
    }
//    free(buffer);
    return (NULL);
}

char	*get_next_line(int fd)
{
    static char	*buffer;
    char		*line;

    if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
        return (NULL);
    buffer = read_file(fd, buffer);
    if (!buffer)
        return (NULL);
    line = read_line(buffer);
    buffer = new_rem(buffer);
    return (line);
}
