/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitelka <aaitelka@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/23 10:02:52 by aaitelka          #+#    #+#             */
/*   Updated: 2024/02/11 00:51:23 by aaitelka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <string.h>

char *read_line(char *buffer)
{
    char    *line;
    size_t  len;

    len = 0;
    while (buffer[len] && buffer[len] != '\n')  //count length of line
        len++;
    if (ft_strchr(buffer, 10))
            len++;                              // add one to include NL character
    if (!len)
        return (NULL);
    line = malloc(len + 1);
    if (!line)
        return (free(buffer), NULL);
    line[len] = '\0';
    while (len--)
        line[len] = buffer[len];
    free(buffer);
    return (line);
}

char *save_rem(char *buffer)
{
    char    *reminder;
    size_t  len;

    if (!buffer)    // if buffer is NULL, return NULL
        return (free(buffer), buffer = NULL, NULL);
    if (ft_strchr(buffer, 10))
        buffer = ft_strchr(buffer, '\n') + 1;
    len = ft_strlen(buffer);
    if (!len)
        return (NULL);
    reminder = calloc(len + 1, 1);
    if (!reminder)
        return (NULL);
    reminder[len] = '\0';
    while (len--)
        reminder[len] = buffer[len];
    return (reminder);
}

char *read_at_nl(int fd)
{
    char        *buffer;
    char        *line;
    ssize_t     ret;

    buffer  = NULL;
    line = NULL;
    buffer = malloc(BUFFER_SIZE + 1);
    if (!buffer)
        return (NULL);
    while ((ret = read(fd, buffer, BUFFER_SIZE)) > 0)
    {
        buffer[ret] = '\0';
        line = join(line, buffer);
        if (ft_strchr(line, 10))
            break;
    }
    free(buffer);
    return (line);
}

char *get_next_line(int fd)
{
    static char *reminder;
    char        *line;

    if (fd < 0 || read(fd, NULL, 0) < 0 || BUFFER_SIZE <= 0)
        return (NULL);
    line = read_at_nl(fd);
    if (reminder)
        line = join(reminder, line);
    reminder = save_rem(line);
   if (!ft_strchr(line, 10))
       reminder = NULL;
    if (line)
        line = read_line(line);
    return (line);
}