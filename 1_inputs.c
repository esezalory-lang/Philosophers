/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_inputs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esezalor <esezalor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 20:52:15 by esezalor          #+#    #+#             */
/*   Updated: 2026/04/29 21:00:41 by esezalor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int argument_handling(int argc, char **argv)
{
    int i;

    i = 1;
    if(argc < 5 || argc > 6)
        return(1);
    while(i < argc)
    {
        if(ft_atoi(argv[i]) <= 0)
            return(1);
        i++;
    }
    return(0);
}