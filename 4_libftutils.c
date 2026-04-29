/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   4_libftutils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esezalor <esezalor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 10:55:19 by esezalor          #+#    #+#             */
/*   Updated: 2026/04/29 15:04:30 by esezalor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_bzero(void *s, size_t n)
{
	memset(s, '\0', n);
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*ptr;
	size_t	i;

	i = 0;
	if (nmemb == 0 || size == 0)
		return (malloc(0));
	if (nmemb > ((size_t)-1) / size)
		return (NULL);
	ptr = malloc(nmemb * size);
	if (ptr == NULL)
		return (NULL);
	while (i < nmemb * size)
		((unsigned char *)ptr)[i++] = 0;
	return (ptr);
}

void	ft_putstr_fd(char *s, int fd)
{
	write(fd, s, ft_strlen(s));
}

long	ft_atoi(const char *nptr)
{
	int			i;
	int			sign;
	long long	new_nbr;

	i = 0;
	sign = 1;
	new_nbr = 0;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			sign = -1;
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		new_nbr = (new_nbr * 10) + (nptr[i] - 48);
		if (new_nbr > INT_MAX || new_nbr < INT_MIN)
			return (2147483648);
		i++;
	}
	return (new_nbr * sign);
}
