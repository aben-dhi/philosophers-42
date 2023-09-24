/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-dhi <aben-dhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 01:43:45 by aben-dhi          #+#    #+#             */
/*   Updated: 2023/09/24 01:44:06 by aben-dhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_and_sleep(t_philo *philo, char *message, int duration)
{
	pthread_mutex_lock(&philo->data->print);
	printf("%lu %d %s\n", get_time() - philo->data->time, philo->id, message);
	pthread_mutex_unlock(&philo->data->print);
	if (duration > 0)
		my_usleep(duration);
}
