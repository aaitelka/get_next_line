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

#include <stdio.h>
#include "get_next_line.h"
#include <unistd.h>
#include <fcntl.h>

void ft_putstr(char *str)
{
    while (*str)
        write(1, str++, 1);
}

 void leaks() {
     system("leaks a.out");
 }

int main(void) {

    //atexit(leaks);
    int fd = open("t", O_RDONLY);
    char *line;
    while (1) {
        line = get_next_line(fd);
        if (!line)
            break ;
        ft_putstr(line);
        write(1,"\n", 1);
        ft_putstr("___________");
        free(line);
    }
    close(fd);
    return 0;
}