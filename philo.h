#ifndef PHILO_H
# define PHILO_H

#include <unistd.h>
#include <stdio.h>
#include "libft.h"
#include <pthread.h>

typedef	struct	s_threads
{
	pthread_t 			thread;
	int					id;
	struct s_threads	*next;
}				t_threads;

typedef struct s_input
{
	int	n_ofphilo;
	int	t_todie;
	int	t_tosleep;
	int	t_toeat;
	int	cicle;
	t_threads	*thread;
}				t_input;



#endif