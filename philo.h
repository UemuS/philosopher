#ifndef PHILO_H
# define PHILO_H

#include <unistd.h>
#include <stdio.h>
#include "libft.h"
#include <pthread.h>
#include <sys/time.h>

struct	t_philos;

typedef struct s_input
{
	int			n_ofphilo;
	int			t_todie;
	int			t_tosleep;
	int			t_toeat;
	int			cicle;

	pthread_mutex_t	*forks;
	pthread_mutex_t	print;
}				t_input;

typedef struct	s_philos
{
	pthread_t	thread;
	int			id;
	int			n_eat;
	int			l_meal;
	t_input		*data;
}				t_philos;





#endif