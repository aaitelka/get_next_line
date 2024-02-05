/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitelka <aaitelka@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/23 10:05:56 by aaitelka          #+#    #+#             */
/*   Updated: 2024/01/02 10:41:09 by aaitelka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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