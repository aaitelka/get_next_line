/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitelka <aaitelka@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/23 10:18:40 by aaitelka          #+#    #+#             */
/*   Updated: 2024/01/03 09:38:03 by aaitelka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 1
#endif

size_t ft_strlen(const char *s) {
    size_t len;

    len = 0;
    while (s[len])
        len++;
    return (len);
}

char *ft_strchr(const char *s, int c) {
    if(!s)
        return (NULL);
    while (*s) {
        if (*s == (char) c)
            return ((char *) s);
        s++;
    }
    if (!(char) c)
        return ((char *) s);
    return (NULL);
}

char *join(char const *s1, char const *s2) {
    char *str;
    size_t s1len;
    size_t s2len;
    size_t dstlen;

    if (!s1 || !s2)
        return (NULL);
    s1len = ft_strlen(s1);
    s2len = ft_strlen(s2);
    dstlen = s1len + s2len;
    str = (char *) malloc(sizeof(char) * (dstlen + 1));
    if (str) {
        while ((*s1 || *s2) && dstlen--) {
            if (*s1)
                *str++ = *s1++;
            else
                *str++ = *s2++;
        }
        *str = '\0';
        str -= (s1len + s2len);
    }
    return (str);
}

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


void leaks() {
    system("leaks a.out");
}

int main(void) {
	atexit(leaks);
    int fd = open("/Users/aaitelka/francinette/tests/get_next_line/fsoares/empty.txt", O_RDONLY);
    int i = 0;
    while (i++ < 1) {
        char *line = get_next_line(fd);
		printf("%s", line);
    }
    close(fd);
    return 0;
}