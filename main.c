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
# define BUFFER_SIZE 100000
#endif

size_t	ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	while (s[len])
		len++;
    return (len);
}

char	*ft_strchr(const char *s, int c)
{
	while (*s)
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	if (!(char)c)
		return ((char *)s);
	return (NULL);
}

char    *join(char const *s1, char const *s2)
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

size_t endl_index(const char *s)
{
    size_t p;

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

    if (fd < 0 || read(fd, NULL, 0) < 0 || BUFFER_SIZE <= 0)
        return (free(buf), NULL);
    if (rem)
        line = rem;
    while ((ret = read(fd, buf, BUFFER_SIZE)) > 0 || *line) {
        if (!ret && !ft_strchr(line, '\n') || ft_strlen(buf) < BUFFER_SIZE)
        {
            rem = NULL;
            break;
        }
        char *endl_c = ft_strchr(buf, '\n');// ?: ft_strchr(line, '\n');
        if (endl_c)
            rem = endl_c + 1;
        line = join(line, buf);
        if (ft_strchr(line, '\n')) {
            line[endl_index(line) + 1] = '\0';
            hasendl = 1;
        }
        if (hasendl)
            break;
    }
    return (line);
}

void leaks()
{
    system("leaks a.out");
}
int main(void)
{
//	atexit(leaks);

    int fd = open("bootstrap.txt", O_RDONLY);
//	int fd = open("README.md", O_RDONLY);

	int i = 0;
	while (i++ < 10)
	{
		char *line = get_next_line(fd);
        if (!line)
        {
            printf("file is empty");
            break;
        }
		printf("%s", line);
        //free(line);
        //line = NULL;
    }
    close(fd);

	return 0;
}