/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yihssan <yihssan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/21 16:01:42 by yihssan           #+#    #+#             */
/*   Updated: 2021/10/21 16:36:37 by yihssan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>

struct	s_philos;

typedef struct s_input
{
	int				n_ofphilo;
	long			t_todie;
	long			t_tosleep;
	long			t_toeat;
	int				cicle;
	long			stime;
	int				gtfo;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print;
}				t_input;

typedef struct s_philos
{
	pthread_t	thread;
	int			id;
	int			n_eat;
	long		l_meal;
	t_input		*data;
}				t_philos;

long		ft_atoi(const char *str);
int			ft_error(char *str);
int			ft_size(char *nmb);
int			isnum(char *str);
void		myusleep(long int	sleeptime);
long int	itsmytime(void);
void		*routine(void *phi);
t_input		*filldata(t_input *data, char **av);
#endif