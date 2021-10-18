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

void		*printtest(void *dta)
{
	t_input *data;


	data = (t_input *)dta;
	pthread_mutex_lock(&(data->print));
	write(1, "hello\n" , 6);
	pthread_mutex_unlock(&(data->print));
	return 0;
}

int	everyone_ate(t_input *data)
{
	int i;

	i = 0;
	while(i < data->n_ofphilo)
	{
		if (data->philos[i].id > data->ate)
			i++;
		else
			return (0);
	}
	return (1);
}

int	make_philos(t_input *data)
{
	int	i;

	i = 0;
	pthread_mutex_init(&(data->print), NULL);
	while(i < data->n_ofphilo)
	{
		if (pthread_create(&(data->philos[i].thread), NULL, &printtest, data) != 0)
			return (1);
		data->philos[i].id = i + 1;
		data->philos[i].n_eat = 0;
		i++;
	}
	i = 0;
	while(i < data->n_ofphilo)
	{
		if (pthread_join(data->philos[i].thread, NULL) != 0)
			return (1);
		i++;
	}
	if (everyone_ate(data))
	{
		data->ate++;
	}
	pthread_mutex_destroy(&(data->print));
	return (0);
}

int	ft_start(int ac, char **av)
{
	t_input	*data;

	data = malloc(sizeof(t_input));
	data->n_ofphilo = ft_atoi(av[1]);
	data->t_todie = ft_atoi(av[2]);
	data->t_toeat = ft_atoi(av[3]);
	data->t_tosleep = ft_atoi(av[4]);
	data->ate = 0;
	if (ac == 6)
		data->cicle = ft_atoi(av[5]);
	else
		data->cicle = -1;
	if ((data->philos = malloc(sizeof(t_philos) * data->n_ofphilo)) == NULL)
	{
		write(2, "failed to allocate\n", 19);
		return (1);
	}
	return (make_philos(data));
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
			return(ft_error("not a valid arg"));
		i++;
	}
	if (ft_atoi(av[1]) > 0)
		return (ft_start(ac,av));
}