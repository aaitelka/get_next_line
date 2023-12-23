/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitelka <aaitelka@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/23 10:05:56 by aaitelka          #+#    #+#             */
/*   Updated: 2023/12/23 11:35:44 by aaitelka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
    size_t	len;

    len = 0;
    while (s[len])
        len++;
    return (len);
}

size_t	endl(const char *s)
{
    int counter;

    counter = 0;
	while (s[counter])
	{
		if (s[counter] == 10)		//endl = newl = 10
			return (counter + 1);	//cause this function when got endl return number of char
		counter++;					//before it that's why i increment it by 1 to get exat position of endl
	}
	return (0);
}

char    *concatenate(char const *s1, char const *s2)
{
    char    *str;
    size_t    s1len;
    size_t    s2len;
    size_t    dstlen;

    if (!s1 || !s2)
        return (NULL);
    s1len = ft_strlen(s1);
    s2len =  ft_strlen(s2);
    dstlen = s1len + s2len;
    str = (char *)malloc(sizeof(char) * (dstlen + 1));
    if (str)
    {
        while ((*s1 || *s2) && dstlen--)
        {
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