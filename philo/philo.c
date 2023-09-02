/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-dhi <aben-dhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 11:20:25 by aben-dhi          #+#    #+#             */
/*   Updated: 2023/09/02 21:45:16 by aben-dhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *pp)
{
	t_philo		*philo;

	philo = (t_philo *)pp;
	if (philo->id % 2 == 0)
		usleep(10);
	philo->last_eat = get_time();
	while (1)
	{
		pthread_mutex_lock(&philo->mutex[philo->id - 1]);
		printf("%lu %d has taken a fork\n",
			get_time() - philo->data->start, philo->id);
		pthread_mutex_lock(&philo->mutex[philo->id % philo->data->philo]);
		printf("%lu %d has taken a fork\n",
			get_time() - philo->data->start, philo->id);
		printf("%lu %d is eating\n", get_time() - philo->data->start, philo->id);
		philo->eat++;
		if (philo->eat == philo->data->must_eat)
			philo->data->all_eat++;
		usleep(philo->data->eat * 1000);
		philo->last_eat = get_time();
		pthread_mutex_unlock(&philo->mutex[philo->id - 1]);
		pthread_mutex_unlock(&philo->mutex[philo->id % philo->data->philo]);
		printf("%lu %d is sleeping\n",
			get_time() - philo->data->start, philo->id);
		usleep(philo->data->sleep * 1000);
		printf("%lu %d is thinking\n",
			get_time() - philo->data->start, philo->id);
	}
	return (0);
}

void	function(t_philo *philo, t_data *data)
{
	int	i;

	i = 0;
	while (1)
	{
		if (philo[i].data->all_eat == philo[i].data->philo)
		{
			// destroy(philo);
			free_p(philo, philo->mutex, data);
			return ;
		}
		if (get_time() - philo[i].last_eat > (unsigned long)data->die)
		{
			usleep(100);
			pthread_mutex_lock(philo->print);
			printf("%lu %d died\n",
				get_time() - philo[i].data->start, philo[i].id);
			// destroy(philo);
			free_p(philo, philo->mutex, data);
			return ;
		}
		i = (i + 1) % data->philo;
		usleep(500);
	}
}

int	main(int argc, char **argv)
{
	int			i;
	t_data		*data;
	t_philo		*philo;
	pthread_t	*thread;

	if (argc < 5 || argc > 6)
		return (exit_error());
	data = (t_data *)malloc(sizeof(t_data));
	if (!data)
		return (printf("Error: malloc failed\n"));
	if (params(data, argv))
		return (free_p(0, 0, data));
	philo = (t_philo *)malloc(sizeof(t_philo) * data->philo);
	if (!philo)
		return (printf("Error: malloc failed\n"));
	if (init(philo, data))
		return (1);
	thread = (pthread_t *)malloc(sizeof(pthread_t) * data->philo);
	if (!thread)
		return (printf("Error: malloc failed\n"));
	i = -1;
	while (++i < philo->data->philo)
	{
		pthread_create(&thread[i], NULL, routine, philo + i);
		usleep(100);
	}
	function(philo, data);
	free(thread);
	return (0);
}
