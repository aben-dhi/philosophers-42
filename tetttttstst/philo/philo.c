/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-dhi <aben-dhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 11:20:25 by aben-dhi          #+#    #+#             */
/*   Updated: 2023/09/24 18:39:03 by aben-dhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	annexe2(t_philo *philo, t_data *data, int i)
{
	pthread_mutex_lock(&data->print);
	if (philo[i].data->eaten == philo[i].data->n_philo)
	{
		pthread_mutex_unlock(&data->print);
		destroy(philo);
		free_all(data, NULL, philo->forks);
		return (-1);
	}
	else
		pthread_mutex_unlock(&data->print);
	return (0);
}

void	annexe(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->print);
	philo->last_eat = get_time();
	pthread_mutex_unlock(&philo->data->print);
	philo->ate++;
	if (philo->data->to_eat != -1 && philo->ate == philo->data->to_eat)
	{
		pthread_mutex_lock(&philo->data->print);
		philo->data->eaten++;
		pthread_mutex_unlock(&philo->data->print);
	}
	pthread_mutex_unlock(&philo->forks[philo->id - 1]);
	pthread_mutex_unlock(&philo->forks[philo->id % philo->data->n_philo]);
	print_and_sleep(philo, "is sleeping", philo->data->t_sleep);
}

void	*eat_sleep_think(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		usleep(10);
	while (1)
	{
		print_and_sleep(philo, "is thinking", 0);
		pthread_mutex_lock(&philo->forks[philo->id - 1]);
		print_and_sleep(philo, "has taken a fork", 0);
		pthread_mutex_lock(&philo->forks[philo->id % philo->data->n_philo]);
		print_and_sleep(philo, "has taken a fork", 0);
		print_and_sleep(philo, "is eating", philo->data->t_eat);
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
		if (annexe2(philo, data, i) == -1)
			break ;
		pthread_mutex_lock(&data->print);
		if (get_time() - philo[i].last_eat
			> (unsigned long)data->t_die)
		{
			pthread_mutex_unlock(&data->print);
			pthread_mutex_lock(&data->print);
			printf("%lu %d died\n", get_time() - philo->data->time, philo[i].id);
			destroy(philo);
			free_all(data, NULL, philo->forks);
			return ;
		}
		pthread_mutex_unlock(&data->print);
		i = (i + 1) % philo->data->n_philo;
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
	data->time = get_time();
	while (++i < philo->data->n_philo)
	{
		philo[i].last_eat = data->time;
		pthread_create(&thread[i], NULL, eat_sleep_think, &philo[i]);
		usleep(10);
	}
	check_ate_and_death(philo, data);
	free(thread);
	return (0);
}
