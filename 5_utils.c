/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3_utils.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esezalor <esezalor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 10:55:19 by esezalor          #+#    #+#             */
/*   Updated: 2026/04/29 20:10:54 by esezalor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"


long int	get_mstime(void)
{
	long int		ms_time;
	struct timeval	current;

	if (gettimeofday(&current, NULL) != 0)
		return (-1);
	ms_time = (current.tv_sec * 1000) + (current.tv_usec / 1000);
	return (ms_time);
}
