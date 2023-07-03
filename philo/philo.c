/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-dhi <aben-dhi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 11:20:25 by aben-dhi          #+#    #+#             */
/*   Updated: 2023/07/03 12:17:55 by aben-dhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_philos(t_philo *philo, int argc, char **argv)
{
	philo->philos = ft_atoi(argv[1]);
	philo->forks = ft_atoi(argv[2]);
	philo->eat = ft_atoi(argv[3]);
	philo->sleep = ft_atoi(argv[4]);
	if (argc == 6)
		philo->must_eat = ft_atoi(argv[5]);
	else
		philo->must_eat = -1;
	if (philo->philos < 2 || philo->forks < 2 || philo->eat < 0 || philo->sleep < 0
		|| philo->must_eat < -1)
	{
		write(1, "Error: wrong arguments\n", 23);
		return (1);
	}
	int i = philo->philos;
	while (i > 0)
		
}
int	main(int argc, char **argv)
{
	t_philo	philo;

	if (argc < 5 || argc > 6)
	{
		write(1, "Error: wrong number of arguments\n", 33);
		return (1);
	}
	philo.philos = ft_atoi(argv[1]);
	philo.forks = ft_atoi(argv[2]);
	philo.eat = ft_atoi(argv[3]);
	philo.sleep = ft_atoi(argv[4]);
	if (argc == 6)
		philo.must_eat = ft_atoi(argv[5]);
	else
		philo.must_eat = -1;
	if (philo.philos < 2 || philo.forks < 2 || philo.eat < 0 || philo.sleep < 0
		|| philo.must_eat < -1)
	{
		write(1, "Error: wrong arguments\n", 23);
		return (1);
	}
	init_philos(&philo, argc, argv);
	return (0);
	
}