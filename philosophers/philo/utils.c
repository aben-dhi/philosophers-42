/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-dhi <aben-dhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 17:48:03 by aben-dhi          #+#    #+#             */
/*   Updated: 2023/09/23 04:31:00 by aben-dhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

unsigned long	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	my_usleep(unsigned long duration)
{
	unsigned long	start;

	start = get_time();
	while (get_time() - start < duration)
		usleep(50);
}

int	exit_error(void)
{
	printf("Error\n");
	printf("use guide:\n num_philo time_to_die time to eat time_to_sleep \
	(must_eat)\n");
	return (1);
}

int	ft_atoi(char *str)
{
	int	i;
	int	n;
	int	sign;

	i = 0;
	n = 0;
	sign = 1;
	while (str[i] == '\t' || str[i] == '\n' || str[i] == '\v' || \
			str[i] == '\f' || str[i] == '\r' || str[i] == ' ')
		i++;
	if (str[i] == '-')
		sign *= -1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	if (str[i] == '\0' || str[i] < '0' || str[i] > '9')
		return (-1);
	while (str[i] >= '0' && str[i] <= '9')
		n = (n * 10) + (str[i++] - '0');
	return (n * sign);
}

void	destroy(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->data->n_philo)
		pthread_mutex_destroy(&philo->forks[i++]);
}
