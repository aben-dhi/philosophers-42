/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-dhi <aben-dhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 11:20:29 by aben-dhi          #+#    #+#             */
/*   Updated: 2023/09/24 16:48:15 by aben-dhi         ###   ########.fr       */
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
	int				n_philo;
	int				t_die;
	int				t_eat;
	int				t_sleep;
	int				to_eat;
	int				eaten;
	unsigned long	time;
	pthread_mutex_t	print;
}t_data;

typedef struct s_philo
{
	int				id;
	int				ate;
	unsigned long	last_eat;
	t_data			*data;
	pthread_mutex_t	*forks;
}t_philo;

int				init(t_data *data, t_philo *philo);
int				check_arg(char **av);
int				arg_to_param(t_data *data, char **av);
void			params(t_philo *philo, t_data *data, pthread_mutex_t *forks);
int				exit_error(void);
int				ft_atoi(char *str);
unsigned long	get_time(void);
int				free_all(t_data *data, t_philo *philo, pthread_mutex_t *mutex);
void			destroy(t_philo *philo);
void			check_ate_and_death(t_philo *philo, t_data *data);
void			my_usleep(unsigned long duration);
void			annexe(t_philo *philo);
int				annexe2(t_philo *philo, t_data *data, int i);
void			print_and_sleep(t_philo *philo, char *message, int duration);

#endif