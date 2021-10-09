#ifndef PHILO_H
# define PHILO_H

#include <unistd.h>
#include <stdio.h>
#include "libft.h"
#include <pthread.h>

typedef	struct	s_philos
{
	pthread_t 			thread;
	int					id;
	int	*n_eat;
}				t_philos;

typedef struct s_input
{
	int			n_ofphilo;
	int			t_todie;
	int			t_tosleep;
	int			t_toeat;
	int			cicle;
	int			n_yeated;
	t_philos	*philos;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print;
}				t_input;



#endif