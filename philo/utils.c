/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-dhi <aben-dhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 17:48:03 by aben-dhi          #+#    #+#             */
/*   Updated: 2023/09/10 22:23:32 by aben-dhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	destroy(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->data->philo)
	{
		pthread_mutex_destroy(&philo[i].fork1);
		pthread_mutex_destroy(philo[i].fork2);
		i++;
	}
}

unsigned long	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

int	free_p(t_philo *philo, pthread_mutex_t *mutex, t_data *data)
{
	if (philo)
		free(philo);
	if (mutex)
		free(mutex);
	if (data)
		free(data);
	return (1);
}

int	ft_atoi(char *str)
{
	int		i;
	int		sign;
	long	nbr;

	i = 0;
	sign = 1;
	nbr = 0;
	while (str[i] == '\t' || str[i] == '\n' || str[i] == '\v' || \
			str[i] == '\f' || str[i] == '\r' || str[i] == ' ')
		i++;
	if (str[i] == '-')
		sign *= -1;
	if ((str[i] == '-') || (str[i] == '+'))
		i++;
	while ((str[i] >= '0') && (str[i] <= '9'))
	{
		if (nbr * sign > 2147483647)
			return (-1);
		if (nbr * sign < -2147483648)
			return (0);
		nbr = (nbr * 10) + (str[i] - '0');
		i++;
	}
	return (nbr * sign);
}

int	exit_error(void)
{
	printf("Error\n");
	printf("Usage: ./philo number_of_philosophers time_to_die time_to_eat ");
	printf("time_to_sleep [number_of_times_each_philosopher_must_eat]\n");
	return (1);
}
