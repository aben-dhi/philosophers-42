/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-dhi <aben-dhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 11:20:29 by aben-dhi          #+#    #+#             */
/*   Updated: 2023/09/10 22:08:20 by aben-dhi         ###   ########.fr       */
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
	unsigned long	start;
}t_data;

typedef struct s_philo
{
	int				id;
	int				eat;
	t_data			*data;
	pthread_mutex_t	fork1;
	pthread_mutex_t	*fork2;
	pthread_mutex_t	*print;
	unsigned long	last_eat;
}t_philo;

int				ft_atoi(char *str);
int				exit_error(void);
int				arg_check(char **arg);
int				params(t_data *data, char **d);
void			assign(t_philo *philo, t_data *d,
					pthread_mutex_t *m1, pthread_mutex_t p);
int				init(t_philo *philo, t_data *data);
void			*routine(void *pp);
void			function(t_philo *philo, t_data *data);
void			destroy(t_philo *philo);
unsigned long	get_time(void);
int				free_p(t_philo *philo, pthread_mutex_t *mutex, t_data *data);

#endif