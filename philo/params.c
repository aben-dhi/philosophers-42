/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   params.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-dhi <aben-dhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 17:42:04 by aben-dhi          #+#    #+#             */
/*   Updated: 2023/09/03 20:13:55 by aben-dhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	arg_check(char **arg)
{
	int	i;
	int	j;

	i = 1;
	while (arg[i])
	{
		j = 0;
		while (arg[i][j])
		{
			if (arg[i][0] == '+')
				j++;
			if ((arg[i][j] < '0' || arg[i][j] > '9'))
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

int	params(t_data *data, char **d)
{
	if (arg_check(d))
		return (exit_error());
	data->all_eat = 0;
	data->start = get_time();
	data->philo = ft_atoi(d[1]);
	data->die = ft_atoi(d[2]);
	data->eat = ft_atoi(d[3]);
	data->sleep = ft_atoi(d[4]);
	if (data->philo <= 0 || data->die <= 0
		|| data->eat <= 0 || data->sleep <= 0)
		return (1);
	if (d[5])
	{
		data->must_eat = ft_atoi(d[5]);
		if (data->must_eat <= 0)
			return (1);
	}
	else
		data->must_eat = -1;
	return (0);
}

void	assign(t_philo *philo, t_data *d,
	pthread_mutex_t m1, pthread_mutex_t p)
{
	int	i;

	i = 0;
	while (i < d->philo)
	{
		philo[i].eat = 0;
		philo[i].id = i + 1;
		philo[i].fork1 = m1;
		philo[i].fork2 = &philo[(i + 1) % d->philo].fork1;
		philo[i].print = &p;
		philo[i].data = d;
		i++;
	}
}

int	init(t_philo *philo, t_data *data)
{
	pthread_mutex_t	m1;
	pthread_mutex_t	p;
	int				i;

	i = 0;
	m1 = (pthread_mutex_t)malloc(sizeof(pthread_mutex_t) * data->philo);
	if (!m1 || !philo)
	{
		return (free_p(philo, &m1, data));
	}
	while (i < data->philo)
		if (pthread_mutex_init(m1[i++], 0))
			return (free_p(philo, &m1, data));
	if (pthread_mutex_init(&p, 0))
		return (free_p(philo, &m1, data));
	assign(philo, data, m1, p);
	return (0);
}
