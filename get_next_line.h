/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitelka <aaitelka@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/23 10:04:04 by aaitelka          #+#    #+#             */
/*   Updated: 2024/02/10 20:31:00 by aaitelka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 10
#endif

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
#include <stdbool.h>

char	*get_next_line(int fd);

size_t	ft_strlen(char *s);

char	*ft_strchr(char *s, int c);

char	*ft_strdup(char *s1);

char	*join(char *s1, char *s2);
#endif