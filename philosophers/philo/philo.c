/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-dhi <aben-dhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 11:20:25 by aben-dhi          #+#    #+#             */
/*   Updated: 2023/09/23 05:01:43 by aben-dhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	annexe2(t_philo *philo, t_data *data, int i)
{
	pthread_mutex_lock(&data->print);
	if (philo[i].data->eaten == philo[i].data->n_philo)
	{
		pthread_mutex_unlock(&data->print);
		destroy(philo);
		free_all(data, philo, philo->forks);
		return ;
	}
	else
		pthread_mutex_unlock(&data->print);
}

void	annexe(t_philo *philo)
{
	pthread_mutex_unlock(&philo->data->print);
	pthread_mutex_lock(&philo->data->print);
	philo->last_eat = get_time();
	pthread_mutex_unlock(&philo->data->print);
	my_usleep(philo->data->t_eat);
	philo->ate++;
	if (philo->data->to_eat != -1 && philo->ate == philo->data->to_eat)
	{
		pthread_mutex_lock(&philo->data->print);
		philo->data->eaten++;
		pthread_mutex_unlock(&philo->data->print);
	}
	pthread_mutex_unlock(&philo->forks[philo->id - 1]);
	pthread_mutex_unlock(&philo->forks[philo->id % philo->data->n_philo]);
	pthread_mutex_lock(&philo->data->print);
	printf("%lu %d is sleeping\n",
		get_time() - philo->data->time, philo->id);
	pthread_mutex_unlock(&philo->data->print);
	my_usleep(philo->data->t_sleep);
}

void	*eat_sleep_think(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		usleep(10);
	pthread_mutex_lock(&philo->data->print);
	philo->last_eat = get_time();
	pthread_mutex_unlock(&philo->data->print);
	while (1)
	{
		pthread_mutex_lock(&philo->data->print);
		printf("%lu %d is thinking\n",
			get_time() - philo->data->time, philo->id);
		pthread_mutex_unlock(&philo->data->print);
		pthread_mutex_lock(&philo->forks[philo->id - 1]);
		printf("%lu %d has taken a fork\n",
			get_time() - philo->data->time, philo->id);
		pthread_mutex_lock(&philo->forks[philo->id % philo->data->n_philo]);
		pthread_mutex_lock(&philo->data->print);
		printf("%lu %d has taken a fork\n",
			get_time() - philo->data->time, philo->id);
		printf("%lu %d is eating\n", get_time() - philo->data->time, philo->id);
		annexe(philo);
	}
	return (NULL);
}

void	check_ate_and_death(t_philo *philo, t_data *data)
{
	int		i;

	i = 0;
	while (1)
	{
		annexe2(philo, data, i);
		pthread_mutex_lock(&data->print);
		if (get_time() - philo[i].last_eat
			> (unsigned long)data->t_die)
		{
			pthread_mutex_unlock(&data->print);
			usleep(100);
			pthread_mutex_lock(&data->print);
			printf("%lu %d died\n", get_time() - philo->data->time, philo[i].id);
			destroy(philo);
			free_all(data, philo, philo->forks);
			return ;
		}
		pthread_mutex_unlock(&data->print);
		i = (i + 1) % philo->data->n_philo;
		usleep(50);
	}
}

int	main(int ac, char **av)
{
	t_data		*data;
	t_philo		*philo;
	pthread_t	*thread;
	int			i;

	if (ac < 5 || ac > 6)
		return (exit_error());
	data = (t_data *)malloc(sizeof(t_data));
	if (arg_to_param(data, av))
		return (free_all(data, NULL, NULL));
	philo = (t_philo *)malloc(sizeof(t_philo) * data->n_philo);
	if (init(data, philo))
		return (1);
	thread = (pthread_t *)malloc(sizeof(pthread_t) * data->n_philo);
	i = -1;
	while (++i < philo->data->n_philo)
	{
		pthread_create(&thread[i], NULL, eat_sleep_think, &philo[i]);
		usleep(100);
	}
	check_ate_and_death(philo, data);
	free(thread);
	return (0);
}
