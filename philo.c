/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yihssan <yihssan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/21 16:01:39 by yihssan           #+#    #+#             */
/*   Updated: 2021/10/21 17:04:45 by yihssan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	everyoneate(t_philos *philos)
{
	int	i;

	i = 0;
	while (i < philos->data->n_ofphilo)
	{
		if (philos[i].n_eat < philos->data->cicle)
			return (0);
		i++;
	}
	return (1);
}

void	create_threads(t_philos *philos)
{
	int	i;

	i = 0;
	while (i < philos->data->n_ofphilo)
	{
		pthread_create(&(philos[i].thread), NULL, &routine, &(philos[i]));
		i += 2;
	}
	myusleep(20);
	i = 1;
	while (i < philos->data->n_ofphilo)
	{
		pthread_create(&(philos[i].thread), NULL, &routine, &(philos[i]));
		i += 2;
	}
}

int	make_philos(t_philos *philos)
{
	int	i;

	i = 0;
	create_threads(philos);
	while (1)
	{
		if (philos->data->cicle > -1 && everyoneate(philos))
		{
			philos[i].data->gtfo = 1;
			break ;
		}
		else if (itsmytime() - philos[i].data->stime - philos[i].l_meal
			> philos[i].data->t_todie)
		{
			philos[i].data->gtfo = 1;
			pthread_mutex_lock(&(philos->data->print));
			printf("%ld : %d died\n", itsmytime()
				- philos[i].data->stime, philos[i].id + 1);
			break ;
		}
		i = (i + 1) % philos[i].data->n_ofphilo;
	}
	return (0);
}

int	ft_start(int ac, char **av)
{
	t_input		*data;
	t_philos	*philos;
	int			i;

	i = -1;
	data = malloc(sizeof(t_input));
	data = filldata(data, av);
	if (ac == 6)
		data->cicle = ft_atoi(av[5]);
	else
		data->cicle = -1;
	philos = malloc(sizeof(t_philos) * data->n_ofphilo);
	while (++i < data->n_ofphilo)
	{
		philos[i].id = i;
		philos[i].n_eat = 0;
		pthread_mutex_init(&(data->forks[i]), NULL);
		philos[i].data = data;
		philos[i].l_meal = 0;
	}
	pthread_mutex_init(&(philos->data->print), NULL);
	return (make_philos(philos));
}

int	main(int ac, char **av)
{
	int	i;

	i = 1;
	if (ac < 5 || ac > 6)
		return (ft_error("Invalid number of arguments\n"));
	while (av[i])
	{
		if (isnum(av[i]) || ft_size(av[i]))
			return (ft_error("Not a valid arg"));
		if (i > 1 && i < 5)
		{
			if (ft_atoi(av[i]) < 60)
				return (ft_error("Number is too small\n"));
		}
		i++;
	}
	if (ft_atoi(av[1]) > 200)
		return (ft_error("Too many philos :))))))))))))\n"));
	if (ft_atoi(av[1]) > 0)
		return (ft_start(ac, av));
}
