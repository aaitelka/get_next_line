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
#include <stddef.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 42
#endif

#define NL 10

size_t ft_strlen(char *s)
{
    size_t len;

    if (!s)
        return (0);
    len = 0;
    while (s[len] != '\0')
        len++;
    return (len);
}

char *ft_strchr(char *s, int c)
{
    if (!s)
        return (NULL);
    while (*s && *s != (char)c)
        s++;
    if (*s == (char)c)
        return (char *)s;
    return (NULL);
}

char *join(char *s1, char *s2)
{
    char *str;
    size_t s1len;
    size_t s2len;
    size_t i;

    if (!s1 && !s2)
        return (NULL);
    if (!s1)
        return (s2);
    s1len = ft_strlen(s1);
    s2len = ft_strlen(s2);
    str = (char *) malloc(sizeof(char) * (s1len + s2len + 1));
    if (!str)
        return (NULL);
    i = -1;
    while (s1[++i])
        str[i] = s1[i];
    int     j = -1;
    while (s2[++j])
        str[i++] = s2[j];
    str[i] = '\0';
    return (str);
}

ssize_t line_length(char *line)
{
    ssize_t length;

    if (!line)
        return (0);
    length = 0;
    while (line[length])
    {
        length++;
        if (line[length] == NL)
            break;
    }
    return (length);
}


char *read_line(char *buffer)
{
    char    *real_line;
    ssize_t length;

    length = line_length(buffer) + 1;
    real_line = (char *) malloc(length + 1);
    if (!real_line)
        return (NULL);
    real_line[length] = '\0';
    while (length--)
        real_line[length] = buffer[length];
    return (real_line);
}

char *save_rem(char *buffer)
{
    char    *remainder;
    ssize_t rem_len;

    if (!buffer || !buffer[0])
        return (NULL);
    buffer = strchr(buffer, NL);
    rem_len = line_length(buffer) + 1;
    remainder = (char *) malloc(rem_len + 1);
    if (!remainder)
        return (NULL);
    remainder[rem_len] = '\0';
    buffer++;
    while (rem_len--)
        remainder[rem_len] = buffer[rem_len];
    return (remainder);
}

// char	*read_file(int fd, char *res)
// {
//     char	*buffer;
//     int		byte_read;

//     buffer = calloc(BUFFER_SIZE + 1, sizeof(char));
//     if (!buffer)
//         return (NULL);
//     while ((byte_read = read(fd, buffer, BUFFER_SIZE)) > 0)
//     {
//         if (byte_read == -1)
//             return (NULL);
//         buffer[byte_read] = 0;
//         res = join(res, buffer);
//         if (ft_strchr(buffer, '\n'))
//             break ;
//     }
//     return (res);
// }

char *get_next_line(int fd)
{
    static char	*buffer;
    char		*line;
    int         byte_read;

    if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
        return (NULL);
    buffer = calloc(BUFFER_SIZE + 1, sizeof(char));
    if (!buffer)
        return (NULL);
    while ((byte_read = read(fd, buffer, BUFFER_SIZE)) > 0)
    {
        if (byte_read <= 0)
            return (NULL);
        buffer[byte_read] = 0;
        line = join(line, buffer);
        if (ft_strchr(buffer, '\n'))
            break ;
    }
    line = read_line(buffer);
    buffer = save_rem(buffer);
    return (line);
}

void leaks() {
    system("leaks a.out");
}

int main(void) {
    atexit(leaks);
    int fd = open("/Users/aaitelka/francinette/tests/get_next_line/fsoares/1char.txt", O_RDONLY);
    int i = 0;
    while (i++ < 1) {
        char *line = get_next_line(fd);
        printf("%s", line);
        free(line);
    }
    close(fd);
    return 0;
}