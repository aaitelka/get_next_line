/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitelka <aaitelka@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/23 10:18:40 by aaitelka          #+#    #+#             */
/*   Updated: 2024/01/01 17:45:33 by aaitelka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 12
#endif

char    *join(char const *s1, char const *s2)
{
    char    *str;
    size_t    s1len;
    size_t    s2len;
    size_t    dstlen;

    if (!s1 || !s2)
        return (NULL);
    s1len = strlen(s1);
    s2len =  strlen(s2);
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

char *get_line(int fd)
{
	static char *rem;
	char *line = "";
	int hasendl = 0;
	char *buf = (char *)malloc(sizeof(char) * BUFFER_SIZE);

	int ret;
	while ((ret = read(fd, buf, BUFFER_SIZE)) > 0)
	{
		if (rem)
			line = join(rem, buf);
		else
			line = join(line, buf);
		
		if (strchr(buf, 10))
			rem = strchr(buf, 10) + 1;
		int i = 0;
		while (line[i] && strchr(line, 10))
		{
			if (line[i] == 10)
			{
				line[i + 1] = '\0'; // add null terminator after endl.
				hasendl = 1;
				break;	
			}
			i++;
		}
		if (hasendl)
			break;
	}
	// printf("\n======================\nrem\n %s\n", rem);
	
	return (line);
}
int main(void)
{
	
	int fd = open("README.md", O_RDONLY);
	
	int i = 0;
	while (i++ < 5)
	{	
		char *line = get_line(fd);
		printf("%s", line);
	}
	return 0;
}