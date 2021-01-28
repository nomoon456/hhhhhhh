/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elbouju <elbouju@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 09:49:26 by pohl              #+#    #+#             */
/*   Updated: 2021/01/27 13:21:21 by elbouju          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>

// void	*ft_calloc(size_t count, size_t size)
// {
// 	void	*buff;
// 	int		length;

// 	length = count * size;
// 	length ? length : length++;
// 	if (!(buff = (void*)malloc((length))))
// 		return (0);
// 	ft_bzero(buff, length);
// 	return (buff);
// }

void	*ft_calloc(size_t count, size_t size)
{
	char	*memory;
	size_t	i;

	i = 0;
	memory = malloc(count * size);
	if (!memory)
		return (0);
	while (i < count * size)
	{
		memory[i] = 0;
		i++;
	}
	return (memory);
}
