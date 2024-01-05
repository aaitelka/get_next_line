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

size_t endl_index(const char *s) {
    size_t p;

    p = 0;
    while (s[p]) {
        if (s[p] == '\n')
            break;
        p++;
    }
    return (p + 1);
}

char *read_line(char *buf) {
    size_t len;
    char *line;

    if (!buf)
        return (free(buf), NULL);
    len = endl_index(buf);
    if (len == 0)
        return (free(buf),NULL);
    line = (char *) malloc(sizeof(char) * (len + 1));
    if (!line)
        return (free(buf), NULL);
    line[len] = '\0';
    while (len)
    {
        len--;
        line[len] = buf[len];
    }
    return (free(buf), line);
}

char *get_next_line(int fd) {
    static char *rem;
    char *line;
    char *buf;
    ssize_t ret;

    line = "";
    buf = (char *) malloc(sizeof(char) * (size_t)(BUFFER_SIZE + 1));
    if (!buf)
        return (NULL);
    if (fd < 0 || read(fd, NULL, 0) < 0 || BUFFER_SIZE <= 0)
        return (free(buf), NULL);
    if (rem)
        line = rem;
    ret = read(fd, buf, BUFFER_SIZE);
    while (*buf || *line) {
        buf[ret] = '\0';
        if (ft_strchr(buf, '\n'))
            rem = ft_strchr(buf, '\n') + 1;
        else if (ft_strchr(line, '\n'))
            rem = ft_strchr(line, '\n') + 1;
        line = join(line, buf);
        if (ft_strchr(line, '\n') || (!ret && !ft_strchr(line, '\n')))
        {
            return (read_line(line));
        }
        ret = read(fd, buf, BUFFER_SIZE);
    }
    free(buf);
    return (NULL);
}
