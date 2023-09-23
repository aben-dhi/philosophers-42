/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   params.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-dhi <aben-dhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 17:42:04 by aben-dhi          #+#    #+#             */
/*   Updated: 2023/09/23 04:34:47 by aben-dhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//checking if the arguments are valid
int	check_arg(char **av)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	while (av[i])
	{
		j = 0;
		while (av[i][j])
		{
			if ((av[i][j] < '0' || av[i][j] > '9') && j != 0)
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

//turning the arguments into our actual parameters
int	arg_to_param(t_data *data, char **av)
{
	if (check_arg(av))
		return (exit_error());
	data->eaten = 0;
	data->time = get_time();
	data->n_philo = ft_atoi(av[1]);
	data->t_die = ft_atoi(av[2]);
	data->t_eat = ft_atoi(av[3]);
	data->t_sleep = ft_atoi(av[4]);
	if (data->n_philo <= 0 || data->t_die <= 0 || data->t_eat <= 0
		|| data->t_sleep <= 0)
		return (1);
	if (av[5])
	{
		data->to_eat = ft_atoi(av[5]);
		if (data->to_eat <= 0)
			return (1);
	}
	else
		data->to_eat = -1;
	return (0);
}

//assigning the parameters to each philosopher
void	params(t_philo *philo, t_data *data, pthread_mutex_t *forks)
{
	int	i;

	i = 0;
	while (i < data->n_philo)
	{
		philo[i].data = data;
		philo[i].id = i + 1;
		philo[i].ate = 0;
		philo[i].forks = forks;
		i++;
	}
}

//freeing everything in case of error
int	free_all(t_data *data, t_philo *philo, pthread_mutex_t *mutex)
{
	if (philo)
		free(philo);
	if (mutex)
		free(mutex);
	if (data)
		free(data);
	return (1);
}

//initializing the mutexes and the parameters
int	init(t_data *data, t_philo *philo)
{
	int				i;
	pthread_mutex_t	*forks;

	i = 0;
	forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * data->n_philo);
	if (!forks || !philo)
		return (free_all(data, philo, forks));
	while (i < data->n_philo)
		if (pthread_mutex_init(&forks[i++], NULL))
			return (free_all(data, philo, forks));
	if (pthread_mutex_init(&data->print, NULL))
		return (free_all(data, philo, forks));
	params(philo, data, forks);
	return (0);
}
