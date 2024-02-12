/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitelka <aaitelka@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/23 10:18:40 by aaitelka          #+#    #+#             */
/*   Updated: 2024/02/12 19:44:25 by aaitelka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include "get_next_line.h"

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
    int i = -1;

    while ( ++i < 7)
    {
        if (i == 2)
            close(fd);
        line = get_next_line(fd);
        if (!line)
            break ;
        ft_putstr(line);
        free(line);
    }
    fd = open("t", O_RDONLY);
    line = get_next_line(fd);
    ft_putstr(line);
    close(fd);
    return 0;
}