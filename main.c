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

char *join(char *s1, char *s2) {
    char *str;
    size_t s1len;
    size_t s2len;
    size_t i;

    if (!s1)
        return (s2);
    if (!s2)
        return (NULL);
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

size_t endl_index(char *s)
{
    size_t i;

    if (!s)
        return (0);
    i = 0;
    while (s[i] && s[i] != '\n')
        i++;
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
    new_rem = (char *) malloc(sizeof(char) * len);
    if (!new_rem)
        return (NULL);
    while (len-- && i++)
        new_rem[i] = rem[i];
    return (new_rem);
}

char	*read_file(int fd, char *res)
{
    char	*buffer;
    int		byte_read;

    buffer = calloc(BUFFER_SIZE + 1, sizeof(char));
    if (!buffer)
        return (NULL);
    while ((byte_read = read(fd, buffer, BUFFER_SIZE)) > 0)
    {
        if (byte_read == -1)
            return (NULL);
        buffer[byte_read] = 0;
        res = join(res, buffer);
        if (ft_strchr(buffer, '\n'))
            break ;
    }
    return (res);
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