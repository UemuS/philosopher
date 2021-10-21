/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philotimeroutine.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yihssan <yihssan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/21 16:26:20 by yihssan           #+#    #+#             */
/*   Updated: 2021/10/21 17:01:40 by yihssan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long int	itsmytime(void)
{
	struct timeval	ctime;

	gettimeofday(&ctime, NULL);
	return ((ctime.tv_sec * 1000) + (ctime.tv_usec / 1000));
}

void	myusleep(long int	sleeptime)
{
	long	end;
	long	start;

	start = itsmytime();
	end = start + sleeptime;
	while (itsmytime() < end)
		usleep(100);
}

int	isnum(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!(str[i] >= 48 && str[i] <= 57))
			return (1);
		i++;
	}
	return (0);
}

void	printroutine(t_philos *philo, char *str)
{
	if (philo->data->gtfo == 1)
		return ;
	pthread_mutex_lock(&(philo->data->print));
	printf("%ld %d %s\n", itsmytime() - philo->data->stime, philo->id + 1, str);
	pthread_mutex_unlock(&(philo->data->print));
}

void	*routine(void *phi)
{
	t_philos	*philo;

	philo = (t_philos *)phi;
	while (1)
	{
		if (philo->data->gtfo == 1)
			return (NULL);
		pthread_mutex_lock(&(philo->data->forks[philo->id]));
		printroutine(philo, "has taken a fork");
		pthread_mutex_lock(&(philo->data->forks[(philo->id - 1
					+ philo->data->n_ofphilo) % philo->data->n_ofphilo]));
		printroutine(philo, "has taken a fork");
		philo->n_eat++;
		philo->l_meal = itsmytime() - philo->data->stime;
		printroutine(philo, "is eating");
		myusleep(philo->data->t_toeat);
		printroutine(philo, "is sleeping");
		pthread_mutex_unlock(&(philo->data->forks[(philo->id - 1
					+ philo->data->n_ofphilo) % philo->data->n_ofphilo]));
		pthread_mutex_unlock(&(philo->data->forks[philo->id]));
		myusleep(philo->data->t_tosleep);
		printroutine(philo, "is thinking");
	}
	return (NULL);
}
