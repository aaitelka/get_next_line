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

char *read_line(char *buffer)
{
    char    *result;
    size_t  len;

    len = 0;
    while (buffer[len] && buffer[len] != '\n')  //count length of line
        len++;
    if (ft_strchr(buffer, 10))
            len++;                              // add one to include NL character
    if (!len)
        return (NULL);
    result = malloc(len + 1);
    if (!result)
        return (free(buffer), NULL);
    result[len] = '\0';
    while (len--)
        result[len] = buffer[len];
    free(buffer);
    return (result);
}

char *save_rem(char *buffer)
{
    char    *result;
    size_t  len;

    if (ft_strchr(buffer, 10))
        buffer = ft_strchr(buffer, '\n') + 1;
    len = ft_strlen(buffer);
    if (!len)
        return (NULL);
    result = malloc(len + 1);
    if (!result)
        return (free(buffer), NULL);
    result[len] = '\0';
    while (len--)
        result[len] = buffer[len];
    //free(buffer);
    return (result);
}

char *get_next_line(int fd)
{
    static char *reminder;
    char        *buffer;
    char        *line;
    ssize_t     ret;

    if (fd < 0 || read(fd, NULL, 0) < 0 || BUFFER_SIZE <= 0)
        return (NULL);
    line = NULL;
    buffer = malloc(BUFFER_SIZE + 1);
    if (!buffer)
        return (free(reminder), NULL);
    while ((ret = read(fd, buffer, BUFFER_SIZE)) > 0)
    {
        buffer[ret] = '\0';
        line = join(line, buffer);
        if (ft_strchr(line, 10))
            break;
    }
    if (reminder)
        line = join(reminder, line);
    if (ft_strchr(line, 10))
        reminder = save_rem(line); //remainder
    if (line)
        line = read_line(line);   //real line
    return (free(buffer), line);
}