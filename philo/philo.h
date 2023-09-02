/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-dhi <aben-dhi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 11:20:29 by aben-dhi          #+#    #+#             */
/*   Updated: 2023/08/16 18:49:35 by aben-dhi         ###   ########.fr       */
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
	pthread_mutex_t	*mutex;
	pthread_mutex_t	*print;
	unsigned long	last_eat;
}t_philo;

int	ft_atoi(char *str);
int	ft_args(int ac, char **av, t_data *data);
void	exit_error(void);

#endif