/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitelka <aaitelka@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/23 10:02:52 by aaitelka          #+#    #+#             */
/*   Updated: 2024/01/03 13:12:21 by aaitelka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

size_t  endl_index(const char *s)
{
	size_t  p;

	p = 0;
	while (s[p])
	{
		if (s[p] == '\n')
			break;
		p++;
	}
	return (p);
}

char *get_next_line(int fd)
{
    static char *rem;
    char *line = "";
    int hasendl = 0;
    ssize_t ret;
    char *buf = (char *)malloc(sizeof(char) * BUFFER_SIZE);

    if (fd < 0 || read(fd, NULL, 0) < 1 || BUFFER_SIZE <= 0)
        return (free(buf), NULL);
    if (rem)
        line = rem;
    while ((ret = read(fd, buf, BUFFER_SIZE)) > 0 || *line) {
        if (!ret && !ft_strchr(line, '\n'))
        {
            rem = NULL;
            break;
        }
        char *endl_c = ft_strchr(buf, '\n') ?: ft_strchr(line, '\n');
        if (endl_c)
            rem = endl_c + 1;
        line = join(line, buf);
        if (ft_strchr(line, '\n')) {
            line[endl_index(line) + 1] = '\0';
            hasendl = 1;
        }
        if (hasendl || ft_strlen(buf) < BUFFER_SIZE)
            break;
    }
    return (line);
}

//char *get_next_line(int fd)
//{
//    static char *rem;
//    char *line = "";
//    int hasendl = 0;
//    ssize_t ret;
//    char *buf = (char *)malloc(sizeof(char) * BUFFER_SIZE);
//
//    if (fd < 0 || read(fd, NULL, 0) < 0 || BUFFER_SIZE <= 0)
//        return (free(buf), NULL);
//    if (rem)
//        line = rem;
//    while ((ret = read(fd, buf, BUFFER_SIZE)) > 0 || *line) {
//        if (ret == 0 && !ft_strchr(line, '\n'))
//        {
//            rem = NULL;
//            break;
//        }
//        char *endl_c = ft_strchr(buf, '\n') ?: ft_strchr(line, '\n');
//        if (endl_c)
//            rem = endl_c + 1;
//
//        line = join(line, buf);
//        if (ft_strchr(line, '\n')) {
//            line[endl_index(line) + 1] = '\0';
//            hasendl = 1;
//        }
//        if (hasendl || ft_strlen(buf) < BUFFER_SIZE)
//            break;
//    }
//    return (line);
//}
//char *get_next_line(int fd)
//{
//    static char *rem = "";
//    char *line;
//    int hasendl = 0;
//    ssize_t ret;
//    char *buf = (char *)malloc(sizeof(char) * BUFFER_SIZE);
//
//    if (fd < 0 || read(fd, NULL, 0) < 0 || BUFFER_SIZE <= 0)
//        return (NULL);
//    if (rem)
//        line = rem;
//    while ((ret = read(fd, buf, BUFFER_SIZE)) > 0 || *line) {
//        if (ret == 0 && !ft_strchr(line, '\n'))
//            break;
//        char *endl_c = ft_strchr(buf, '\n') ?: ft_strchr(line, '\n');
//        if (endl_c)
//            rem = endl_c + 1;
//
//        line = join(line, buf);
//        if (ft_strchr(line, '\n')) {
//            line[endl_index(line) + 1] = '\0';
//            hasendl = 1;
//        }
//        if (hasendl || ft_strlen(buf) < BUFFER_SIZE)
//            break;
//    }
//    return (line);
//}
//char *get_next_line(int fd)
//{
//	static char *rem = "";
//	char *line;
//	int hasendl = 0;
//	ssize_t ret;
//	char *buf = (char *)malloc(sizeof(char) * BUFFER_SIZE);
//
//    if (fd >= 0 && read(fd, NULL, 0) >= 1 && BUFFER_SIZE >= 1) {
//        if (rem)
//            line = rem;
//        while ((ret = read(fd, buf, BUFFER_SIZE)) > 0 || *line) {
//            if (ret == 0)
//                break;
//            char *endl_c = ft_strchr(buf, '\n');
//
//            line = join(line, buf);
//            if (endl_c)
//                rem = endl_c + 1;
//            if (ft_strchr(line, '\n')) {
//                line[endl_index(line) + 1] = '\0';
//                hasendl = 1;
//            }
//            if (hasendl || ft_strlen(buf) < BUFFER_SIZE)
//                break;
//        }
//        return (line);
//    }
//    return (free(buf), NULL);
//}

