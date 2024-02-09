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

char *read_line_or_save_rem(char *buffer, bool is_line)
{
    char    *result;
    size_t  len;

    len = 0;
    if (is_line)
        while (buffer[len] && buffer[len] != '\n') //count length of line
            len++;
    else {
        if (ft_strchr(buffer, 10))
            buffer = ft_strchr(buffer, '\n') + 1;
        len = ft_strlen(buffer);
    }
    len++; // add one to include NL character
    result = (char *) malloc(sizeof(char) * (len + 1));
    if (!result)
        return (NULL);
    result[len] = '\0';
    while (len--)
        result[len] = buffer[len];
    return (result);
}

char *get_next_line(int fd)
{
    static char *rem;
    char *buffer;
    char *line;
    ssize_t ret;

    line = "";
    buffer = malloc(BUFFER_SIZE + 1);
    while ((ret = read(fd, buffer, BUFFER_SIZE)) > 0) {
        buffer[ret] = '\0';
        line = join(line, buffer);
        if (ft_strchr(line, 10))
            break;
    }
    if (rem)
        line = join(rem, line);
    if (ft_strchr(line, 10))
        rem = read_line_or_save_rem(line, false); //remainder
    else
        rem = NULL;
    line = read_line_or_save_rem(line, true);   //real line
    free(buffer);
    return (line);
}
