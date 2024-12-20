/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safesyscall.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mes-salh <mes-salh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 17:19:01 by mes-salh          #+#    #+#             */
/*   Updated: 2024/11/10 05:23:40 by mes-salh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosofers.h"

void	*safe_malloc(size_t size)
{
	void	*ptr;

	ptr = malloc(size);
	if (!ptr)
	{
		printf("Error: malloc failed\n");
		return (NULL);
	}
	return (ptr);
}
