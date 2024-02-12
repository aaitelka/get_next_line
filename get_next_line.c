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

char *read_line(char *buffer) {
    char *line;
    size_t len;

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

char *save_rem(char *reminder, char *line) {
    size_t len;

    if (!line)
        return (NULL);
    line = ft_strchr(line, '\n') + 1;
    len = ft_strlen(line);
    if (!len)
        return (NULL);
    reminder = malloc(len + 1);
    if (!reminder)
        return (free(line), NULL);
    reminder[len] = '\0';
    while (len--)
        reminder[len] = line[len];
    return (reminder);
}

void read_at_nl(int fd, char **line)
{
    static char *reminder;
    char *buffer;

    ssize_t ret;
    buffer = malloc(BUFFER_SIZE + 1);
    if (!buffer)
        return;
    *line = reminder;
    reminder = NULL;
    ret = 1;
    while (ret > 0) {
        ret = read(fd, buffer, BUFFER_SIZE);
        if (ret == -1) {
            free(buffer);
            reminder = NULL;
            return;
        }
        buffer[ret] = '\0';
        *line = join(*line, buffer);
        if (ft_strchr(*line, 10))
            break;
    }
    if (ft_strchr(*line, 10))
        reminder = save_rem(reminder, *line);
    free(buffer);
}

char *get_next_line(int fd)
{
    char *line;

    if (fd < 0 || read(fd, NULL, 0) < 0 || BUFFER_SIZE <= 0)
        return (NULL);
    read_at_nl(fd, &line);
    if (!line)
        return (NULL);
    return (read_line(line));
}