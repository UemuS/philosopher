/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philotools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yihssan <yihssan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/21 16:24:43 by yihssan           #+#    #+#             */
/*   Updated: 2021/10/21 16:37:08 by yihssan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_input	*filldata(t_input *data, char **av)
{
	struct timeval	starttime;

	gettimeofday(&starttime, NULL);
	data->stime = (starttime.tv_sec * 1000) + (starttime.tv_usec / 1000);
	data->n_ofphilo = ft_atoi(av[1]);
	data->t_todie = ft_atoi(av[2]);
	data->t_toeat = ft_atoi(av[3]);
	data->t_tosleep = ft_atoi(av[4]);
	data->gtfo = 0;
	data->forks = malloc(sizeof(pthread_mutex_t) * data->n_ofphilo);
	return (data);
}

size_t	ft_strlen(const char *s)
{
	size_t	l;

	l = 0;
	while (s[l] != '\0')
		l++;
	return (l);
}

int	ft_size(char *nmb)
{
	if (ft_strlen(nmb) > 11 || ft_atoi(nmb) < 0)
		return (1);
	return (0);
}

int	ft_error(char *str)
{
	write(1, str, ft_strlen(str));
	return (2);
}

long	ft_atoi(const char *str)
{
	size_t	l;
	long	res;
	int		sign;

	l = 0;
	res = 0;
	sign = 1;
	while (str[l] != '\0' && ((str[l] >= 9 && str[l] <= 13) || str[l] == 32))
		l++;
	if (str[l] == '-')
		sign = -1;
	if (str[l] == '-' || str[l] == '+')
		l++;
	while (str[l] != '\0' && str[l] >= 48 && str[l] <= 57)
		res = res * 10 + str[l++] - '0';
	return (res * sign);
}
