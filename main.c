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