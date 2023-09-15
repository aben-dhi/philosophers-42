/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-dhi <aben-dhi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 11:20:25 by aben-dhi          #+#    #+#             */
/*   Updated: 2023/09/15 01:20:57 by aben-dhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

unsigned long	current_time(t_philo *philo)
{
	return (get_time() - philo->data->start);
}

void	print(t_philo *philo, unsigned long time, char *action)
{
	pthread_mutex_lock(philo->print);
	printf("%lu	%d %s\n", time, philo->id, action);
	pthread_mutex_unlock(philo->print);
}

void	*routine(void *pp)
{
	t_philo		*philo;

	philo = (t_philo *)pp;
	if (philo->id % 2 == 0)
		usleep(10);
	pthread_mutex_lock(&philo->check);
	philo->last_eat = get_time();
	pthread_mutex_unlock(&philo->check);
	while (1)
	{
		// Introduce a delay here
    	// usleep(100);
		pthread_mutex_lock(&philo->fork[philo->id - 1]);
		print(philo, current_time(philo), "has taken a fork");
		// 	// Check if the philosopher should not eat and return if so
		// if (philo->data->philo == 1) {
		// 	pthread_mutex_unlock(&philo->fork1);
		// 	break ;  // Return from the thread
		// }
		pthread_mutex_lock(&philo->fork[philo->id % philo->data->philo]);
		print(philo, current_time(philo), "has taken a fork");
		print(philo, current_time(philo), "is eating");

		// if (philo->data->must_eat != -1 && philo->eat >= philo->data->must_eat) {
        //     pthread_mutex_unlock(&philo->fork1);
        //     pthread_mutex_unlock(philo->fork2);
        //     return NULL;  // Return from the thread
        // }
		philo->eat++;
		if (philo->eat == philo->data->must_eat)
            philo->data->all_eat++;
		usleep(philo->data->eat * 1000);
		pthread_mutex_lock(&philo->check);
		philo->last_eat = get_time();
		pthread_mutex_unlock(&philo->check);
		pthread_mutex_unlock(&philo->fork[philo->id - 1]);
		pthread_mutex_unlock(&philo->fork[philo->id % philo->data->philo]);
		print(philo, current_time(philo), "is sleeping");
		usleep(philo->data->sleep * 1000);
		print(philo, current_time(philo), "is thinking");
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
			destroy(philo);
			free_p(philo, NULL, data);
			return ;
		}
		pthread_mutex_lock(&philo->check);
		if (get_time() - philo[i].last_eat > (unsigned long)data->die)
		{
			pthread_mutex_unlock(&philo->check);
			usleep(100);
			pthread_mutex_lock(philo->print);
			printf("%lu %d died\n",
				current_time(philo), philo->id);
			destroy(philo);
			free_p(philo, NULL, data);
			return ;
		}
		pthread_mutex_unlock(&philo->check);
		// if (data->must_eat != -1 && philo[i].eat == data->must_eat)
		// {
		// 	i = (i + 1) % data->philo;
		// 	continue ;
		// }
		// if (data->philo == 1 && philo[i].eat >= data->must_eat)
        // {
        //     pthread_mutex_unlock(philo->print);
        //     return;
        // }
		i = (i + 1) % data->philo;
		usleep(500);
	}
}

// void function(t_philo *philo, t_data *data)
// {
//     int i;
// 	unsigned long start_time = get_time();

//     i = 0;
//     while (1)
//     {
// 		if (data->philo == 1 && get_time() - start_time > (unsigned long)data->die)
//         {
//             pthread_mutex_lock(philo->print);
//             printf("%lu %d died\n",
//                    get_time() - philo[i].data->start, philo[i].id);
//             destroy(philo);
//             free_p(philo, NULL, data);
//             return;
//         }
//         if (get_time() - philo[i].last_eat > (unsigned long)data->die)
//         {
//             usleep(100);
//             pthread_mutex_lock(philo->print);
//             printf("%lu %d died\n",
//                    get_time() - philo[i].data->start, philo[i].id);
//             destroy(philo);
//             free_p(philo, NULL, data);
//             return;
//         }
//         if (philo[i].data->all_eat == philo[i].data->philo)
//         {
//             destroy(philo);
//             free_p(philo, NULL, data);
//             return;
//         }
//         i = (i + 1) % data->philo;
//         usleep(500);
//     }
// }

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
