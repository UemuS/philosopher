#include "philo.h"

int	isnum(char *str)
{
	int	i;

	i = 0;
	while(str[i])
	{
		if (!ft_isdigit(str[i]))
			return (1);
		i++;
	}
	return (0);
}

int	ft_size(char *nmb)
{
	if (ft_strlen(nmb) > 11 || ft_atoi(nmb) > 500
		|| ft_atoi(nmb) < 0)
		return (1);
	return (0);
}

int	ft_error(char *str)
{
	write(1, str, ft_strlen(str));
	return(2);
}

void	*printtest(void *phi)
{
	t_philos *philo;

	philo = (t_philos *)phi;
	pthread_mutex_lock(&(philo->data->forks[philo->id]));
	pthread_mutex_lock(&(philo->data->forks[(philo->id -1 + philo->data->n_ofphilo) % philo->data->n_ofphilo]));
	philo->n_eat++;
	pthread_mutex_lock(&(philo->data->print));
	printf("Philo number %d is eating fork id %d\n", philo->id, (philo->id - 1 + philo->data->n_ofphilo) % philo->data->n_ofphilo);
	pthread_mutex_unlock(&(philo->data->print));
	pthread_mutex_unlock(&(philo->data->forks[philo->id ]));
	pthread_mutex_unlock(&(philo->data->forks[(philo->id -1 + philo->data->n_ofphilo) % philo->data->n_ofphilo]));
	return NULL;
}

int	make_philos(t_philos *philos)
{
	int	i;

	i = 0;
	philos->data->forks = malloc(sizeof(pthread_mutex_t) * philos->data->n_ofphilo);
	pthread_mutex_init(&(philos->data->print), NULL);
	while(i < philos->data->n_ofphilo)
	{
		pthread_create(&(philos[i].thread), NULL, &printtest, &(philos[i]));
		i+=2;
	}
	usleep(200);
	i = 1;
	while(i < philos->data->n_ofphilo)
	{
		pthread_create(&(philos[i].thread), NULL, &printtest, &(philos[i]));
		i+=2;
	}
	i = -1;
	while(++i < philos->data->n_ofphilo)
	{
		pthread_join(philos[i].thread, NULL);
	}
	i = -1;
	// while(++i < philos->data->n_ofphilo)
	// 	printf("Philo number %d ate and reporting for duty \n", philos[i].id);
	return (0);
}

int	ft_start(int ac, char **av)
{
	t_input		*data;
	t_philos	*philos;
	int			i;

	i = -1;
	data = malloc(sizeof(t_input));
	data->n_ofphilo = ft_atoi(av[1]);
	data->t_todie = ft_atoi(av[2]);
	data->t_toeat = ft_atoi(av[3]);
	data->t_tosleep = ft_atoi(av[4]);
	if (ac == 6)
		data->cicle = ft_atoi(av[5]);
	else
		data->cicle = -1;
	if ((philos = malloc(sizeof(t_philos) * data->n_ofphilo)) == NULL)
	{
		write(2, "failed to allocate\n", 19);
		return (1);
	}
	while(++i < data->n_ofphilo)
	{
		philos[i].id = i;
		philos[i].n_eat = 0;
		philos[i].data = data;
	}
	return (make_philos(philos));
}

int	main(int ac, char **av)
{
	int	i;

	i = 1;
	if (ac < 5 || ac > 6)
		return (ft_error("Invalid number of arguments"));
	while(av[i])
	{
		if (isnum(av[i]) || ft_size(av[i]))
			return(ft_error("Not a valid arg"));
		if (i > 1 && i < 5)
		{
			if (ft_atoi(av[i]) < 60)
				return (ft_error("Number is too small"));
		}
		i++;
	}
	if (ft_atoi(av[1]) > 0)
		return (ft_start(ac,av));
}