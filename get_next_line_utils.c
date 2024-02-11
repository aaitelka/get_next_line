/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitelka <aaitelka@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/23 10:05:56 by aaitelka          #+#    #+#             */
/*   Updated: 2024/02/11 00:48:57 by aaitelka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <string.h>

size_t ft_strlen(char *s) {
    size_t len;

    if (!s)
        return (0);
    len = 0;
    while (s[len] != '\0')
        len++;
    return (len);
}

char *ft_strchr(char *s, int c) {
    if (!s)
        return (NULL);
    while (*s && *s != (char) c)
        s++;
    if (*s == (char) c)
        return (char *) s;
    return (NULL);
}

char *ft_strdup(char *src) {
    char *new;
    int i;
    int size;

    size = 0;
    while (src[size])
        size++;
    if (!(new = malloc(sizeof(char) * (size + 1))))
        return (NULL);
    i = 0;
    while (src[i]) {
        new[i] = src[i];
        i++;
    }
    new[i] = '\0';
    return (new);
}

char *join(char *s1, char *s2) {
    char *str;
    size_t i;
    size_t j;

    if (!s1)
        return (strdup(s2));
    if (!s2)
        return (strdup(s1));
    str = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
    if (!str)
        return (NULL);
    i = -1;
    while (s1[++i])
        str[i] = s1[i];
    j = -1;
    while (s2[++j])
        str[i++] = s2[j];
    str[i] = '\0';
    free(s1);
    return (str);
}