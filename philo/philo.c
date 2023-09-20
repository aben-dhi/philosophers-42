/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-dhi <aben-dhi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 11:20:25 by aben-dhi          #+#    #+#             */
/*   Updated: 2023/09/20 21:09:39 by aben-dhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	current_time(t_philo *philo)
{
	return (get_time() - philo->data->start);
}

void	print(t_philo *philo, long long time, char *action)
{
	pthread_mutex_lock(&philo->data->check);
	if (philo->data->kill == 0)
		printf("%lld %d %s\n", time, philo->id, action);
	pthread_mutex_unlock(&philo->data->check);
}

void	my_usleep(t_philo *philo, int to)
{
	long long	start;

	start = get_time();
	while (get_time() - start < to)
	{
		pthread_mutex_lock(&philo->data->check);
		if (philo->data->kill == 1)
		{
			pthread_mutex_unlock(&philo->data->check);
			break ;
		}
		pthread_mutex_unlock(&philo->data->check);
		usleep(200);
	}
}

void	*routine(void *pp)
{
	t_philo		*philo;

	philo = (t_philo *)pp;
	if (philo->id % 2 == 0)
		usleep(100);
	while (1)
	{
		print(philo, current_time(philo), "is thinking");
		pthread_mutex_lock(&philo->fork1);
		print(philo, current_time(philo), "has taken a fork");
		pthread_mutex_lock(philo->fork2);
		print(philo, current_time(philo), "has taken a fork");
		print(philo, current_time(philo), "is eating");
		philo->eat++;
		// if (philo->data->must_eat != -1 && philo->eat >= philo->data->must_eat) {
        //     pthread_mutex_unlock(&philo->fork1);
        //     pthread_mutex_unlock(philo->fork2);
        //     return NULL;  // Return from the thread
        // }
		pthread_mutex_lock(&philo->data->check);
		philo->last_eat = get_time();
		pthread_mutex_unlock(&philo->data->check);
		my_usleep(philo, philo->data->eat);
		pthread_mutex_unlock(&philo->fork1);
		pthread_mutex_unlock(philo->fork2);
		print(philo, current_time(philo), "is sleeping");
		my_usleep(philo, philo->data->sleep);
		// if (philo->data->must_eat != -1 && philo->eat >= philo->data->must_eat)
		// {
		// 	// printf("");
		// 	pthread_mutex_lock(&philo->data->check);
		// 	philo->data->all_eat++;
		// 	pthread_mutex_unlock(&philo->data->check);
		// }
	}
	return (NULL);
}

void	function(t_philo *philo, t_data *data)
{
	int	i;
	int	time;

	i = 0;
	while (1)
	{
		// pthread_mutex_lock(&philo->data->check);
		// if (philo[i].data->all_eat == philo[i].data->philo)
		// {
		// 	destroy(philo);
		// 	free_p(philo, NULL, data);
		// 	pthread_mutex_unlock(&philo->data->check);
		// 	return ;
		// }
		// pthread_mutex_unlock(&philo->data->check);
		pthread_mutex_lock(&philo->data->check);
		time = get_time() - philo[i].last_eat;
		pthread_mutex_unlock(&philo->data->check);
		if (time >= data->die)
		{
			// pthread_mutex_lock(&philo->data->var);
			pthread_mutex_lock(&philo->data->check);
			philo->data->kill = 1;
			// pthread_mutex_unlock(&philo->data->var);
			pthread_mutex_unlock(&philo->data->check);
			printf("%lld %d died\n", current_time(philo), philo[i].id);
			if (data->philo == 1)
				pthread_mutex_unlock(&philo->fork1);
			return ;
		}
		// pthread_mutex_unlock(&philo->data->check);
		// if (data->must_eat != -1 && philo[i].eat == data->must_eat)
		// {
		// 	i = (i + 1) % data->philo;
		// 	continue ;
		// }
		i = (i + 1) % data->philo;
	}
}

int	main(int argc, char **argv)
{
	int			i;
	t_data		data;
	t_philo		*philo;

	if (argc < 5 || argc > 6)
		return (exit_error());
	if (params(&data, argv))
		return (1);
	philo = (t_philo *)malloc(sizeof(t_philo) * data.philo);
	if (!philo)
		return (printf("Error: malloc failed\n"));
	init(philo, &data);
	i = -1;
	while (++i < data.philo)
	{
		// philo[i].start = get_time();
		philo[i].last_eat = get_time();
		pthread_create(&philo[i].thread, NULL, routine, &philo[i]);
		// pthread_mutex_lock(&data.check);
		// pthread_mutex_unlock(&data.check);
		usleep(10);
	}
	function(philo, &data);
	// destroy(philo);
	free(philo);
	return (0);
}
//retest ./philo 4 410 200 200 (shouldnt die)

