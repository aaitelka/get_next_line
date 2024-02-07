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

size_t ft_strlen(const char *s)
{
    size_t len;

    len = 0;
    while (s[len])
        len++;
    return (len);
}

char *ft_strchr(const char *s, int c)
{
    while (*s) {
        if (*s == (char) c)
            return ((char *) s);
        s++;
    }
    if (!(char) c)
        return ((char *) s);
    return (NULL);
}

char *join(char const *s1, char const *s2)
{
    char	*str;
    size_t	i;
    size_t	j;

    if (!s1 && !s2)
        return (NULL);
    str = malloc((ft_strlen(s1) + ft_strlen(s2)) + 1);
    if (!str)
        return (NULL);
    i = -1;
    while (s1[++i])
        str[i] = s1[i];
    j = -1;
    while (s2[++j])
        str[i++] = s2[j];
    str[i] = '\0';
    if (*s1)
        free((char *)s1);
    return (str);
}