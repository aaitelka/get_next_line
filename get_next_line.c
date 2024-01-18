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

    if (!buf || *buf == '\0')
        return (NULL);
    len = endl_index(buf);
    if (len == 0)
        return (free(buf), NULL);
    line = (char *) malloc(sizeof(char) * (len + 1));
    if (!line)
        return (free(buf), NULL);
    line[len] = '\0';
    while (len--)
        line[len] = buf[len];
    return (free(buf), line);
}

char *new_rem(const char *rem)
{
    char *new_rem;
    size_t mlen;
    size_t len;

    if (!rem)
        return (NULL);
    rem = strchr(rem, 10) + 1;
    len = endl_index(rem);
    mlen = len;
    new_rem = (char *) malloc(sizeof(char) * len);
    if (!new_rem)
        return (NULL);
    while (*rem && len--)
        *new_rem++ = *rem++;
    *new_rem = '\0';
    new_rem -= mlen - 1;
    return (new_rem);
}


char *get_next_line(int fd) {
    static char *rem;
    char *buf;
    ssize_t ret;

    buf = (char *) malloc(sizeof(char) * (size_t) (BUFFER_SIZE + 1));
    if (!buf)
        return (NULL);
    if (fd < 0 || read(fd, NULL, 0) < 0 || BUFFER_SIZE <= 0)
        return (free(buf), NULL);
    ret = read(fd, buf, BUFFER_SIZE);
    while (*buf || *rem) {
        buf[ret] = '\0';
        if (ft_strchr(buf, '\n'))
            rem = ft_strchr(buf, '\n') + 1;
        else if (ft_strchr(rem, '\n'))
        {
            new_rem(rem);
//            break;
        }
        rem = join(rem, buf);
        if (ft_strchr(rem, '\n') || ft_strchr(buf, 10) || (!ret && !ft_strchr(rem, '\n'))) {
            return (free(buf), read_line(rem));
        }
        ret = read(fd, buf, BUFFER_SIZE);
    }
    free(buf);
    return (read_line(rem));
}
