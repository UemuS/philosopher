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
	if (ft_strlen(nmb) > 11 || ft_atoi(nmb) > INT_MAX
		|| ft_atoi(nmb) < INT_MIN)
		return (1);
	return (0);
}

int	ft_error(char *str)
{
	write(1, str, ft_strlen(str));
	return(2);
}

void	ft_start(int ac, char **av)
{
	t_input	*data;

	data = malloc(sizeof(t_input));
	data->n_ofphilo = ft_atoi(av[1]);
	data->t_todie = ft_atoi(av[2]);
	data->t_toeat = ft_atoi(av[3]);
	data->t_tosleep = ft_atoi(av[4]);
	if (ac == 6)
		data->cicle = ft_atoi(av[5]);
	else
		data->cicle = -1;
	printf("number = %d | time to die = %d | time to eat = %d | time to sleep = %d | cicle = %d\n", data->n_ofphilo, data->t_todie, data->t_toeat, data->t_tosleep, data->cicle);
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
			return(ft_error("arg is not a valid number"));
		i++;
	}
	ft_start(ac,av);
}