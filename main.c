/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitelka <aaitelka@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/23 10:18:40 by aaitelka          #+#    #+#             */
/*   Updated: 2024/02/11 00:23:12 by aaitelka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include "get_next_line.h"

//size_t ft_strlen(char *s) {
//    size_t len;
//
//    if (!s)
//        return (0);
//    len = 0;
//    while (s[len] != '\0')
//        len++;
//    return (len);
//}
//
//char *ft_strchr(char *s, int c) {
//    if (!s)
//        return (NULL);
//    while (*s && *s != (char) c)
//        s++;
//    if (*s == (char) c)
//        return (char *) s;
//    return (NULL);
//}
//
//char *ft_strdup(char *src) {
//    char *new;
//    int i;
//    int size;
//
//    size = 0;
//    while (src[size])
//        size++;
//    if (!(new = malloc(sizeof(char) * (size + 1))))
//        return (NULL);
//    i = 0;
//    while (src[i]) {
//        new[i] = src[i];
//        i++;
//    }
//    new[i] = '\0';
//    return (new);
//}
//
//char *join(char *s1, char *s2) {
//    char *str;
//    size_t i;
//    size_t j;
//
//    if (!s1)
//        return (strdup(s2));
//    if (!s2)
//        return (strdup(s1));
//    str = calloc(ft_strlen(s1) + ft_strlen(s2) + 1, 1);
//    if (!str)
//        return (NULL);
//    i = -1;
//    while (s1[++i])
//        str[i] = s1[i];
//    j = -1;
//    while (s2[++j])
//        str[i++] = s2[j];
//    str[i] = '\0';
//    free(s1);
//    return (str);
//}
//
//char *read_line(char *buffer) {
//    char *line;
//    size_t len;
//
//    len = 0;
//    while (buffer[len] && buffer[len] != '\n')  //count length of line
//        len++;
//    if (buffer[len] == '\n')
//        len++;                              // add one to include NL character
//    if (!len)
//        return (NULL);
//    line = (char *)malloc(len + 1);
//    if (!line)
//        return (free(buffer), NULL);
//    line[len] = '\0';
//    while (len--)
//        line[len] = buffer[len];
//    free(buffer);
//    return (line);
//}
//
//char *save_rem(char *buffer) {
//    char *reminder;
//    size_t len;
//
//    if (!buffer)    // if buffer is NULL, return NULL
//        return (free(buffer), buffer = NULL, NULL);
//    if (ft_strchr(buffer, 10))
//        buffer = ft_strchr(buffer, '\n') + 1;
//    len = ft_strlen(buffer);
//    if (!len)
//        return (NULL);
//    reminder = malloc(len + 1);
//    if (!reminder)
//        return (free(buffer), NULL);
//    reminder[len] = '\0';
//    while (len--)
//        reminder[len] = buffer[len];
////    free(buffer);
//    return (reminder);
//}
//
//char *read_at_nl(int fd) {
//    char *buffer;
//    char *line;
//    ssize_t ret;
//
//    if (fd < 0)
//        return (NULL);
//    buffer = NULL;
//    line = NULL;
//    buffer = calloc(BUFFER_SIZE + 1, 1);
//    if (!buffer)
//        return (NULL);
//    ret = 1;
//    while (ret) {
//        ret = read(fd, buffer, BUFFER_SIZE);
//        if (ret == -1)
//            return (free(buffer), NULL);
//        buffer[ret] = '\0';
//        line = join(line, buffer);
//        if (!line)
//            return (free(buffer), NULL);
//        if (ft_strchr(line, 10))
//            break;
//    }
//    free(buffer);
//    return line;
//}
//
//char *get_next_line(int fd) {
//    static char *reminder;
//    char *line;
//
//    if (fd < 0 || read(fd, NULL, 0) < 0 || BUFFER_SIZE <= 0)
//        return (NULL);
//    line = read_at_nl(fd);
//    if (reminder)
//        line = join(reminder, line);
//    reminder = save_rem(line);
//    if (!ft_strchr(line, 10))
//        reminder = NULL;
//    if (line)
//        line = read_line(line);
//    return (line);
//}

void ft_putstr(char *str)
{
    while (*str)
        write(1, str++, 1);
}

 void leaks() {
     system("leaks a.out");
 }

int main(void) {

    int fd = open("t", O_RDONLY);
    char *line;
    int i = 0;

    while (i++ < 60)
    {
        line = get_next_line(fd);
        if (!line)
            break ;
        ft_putstr(line);
        free(line);
    }
    close(fd);
    return 0;
}