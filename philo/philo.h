/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-dhi <aben-dhi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 11:20:29 by aben-dhi          #+#    #+#             */
/*   Updated: 2023/09/20 20:54:15 by aben-dhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h> 
# include <pthread.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/time.h> 

typedef struct s_data
{
	int				philo;
	int				die;
	int				eat;
	int				sleep;
	int				must_eat;
	int				all_eat;
	int				kill;
	// int				*all_eat;
	long long		start;
	pthread_mutex_t	check;
	pthread_mutex_t	var;
}t_data;

typedef struct s_philo
{
	int				id;
	int				eat;
	pthread_t		thread;
	pthread_mutex_t	fork1;
	pthread_mutex_t	*fork2;
	long long		last_eat;
	t_data			*data;
}t_philo;

int				ft_atoi(char *str);
int				exit_error(void);
int				arg_check(char **arg);
int				params(t_data *data, char **d);
void			assign(t_philo *philo, t_data *d);
void			init(t_philo *philo, t_data *data);
void			*routine(void *pp);
void			function(t_philo *philo, t_data *data);
void			destroy(t_philo *philo);
long long		get_time(void);
int				free_p(t_philo *philo, pthread_mutex_t *mutex, t_data *data);
void			print(t_philo *philo, long long time, char *action);
long long		current_time(t_philo *philo);

#endif