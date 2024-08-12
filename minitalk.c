/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrazanad <mrazanad@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 13:32:58 by mrazanad          #+#    #+#             */
/*   Updated: 2024/08/08 10:32:02 by mrazanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	setup_signal_handler(struct sigaction *sa)
{
	if (sigaction(SIGUSR1, sa, NULL) == -1)
	{
		ft_putstr_fd("sigaction error\n", 2);
		exit(EXIT_FAILURE);
	}
	if (sigaction(SIGUSR2, sa, NULL) == -1)
	{
		ft_putstr_fd("sigaction error\n", 2);
		exit(EXIT_FAILURE);
	}
}

void	send_char_message(pid_t pid, char message)
{
	int		swith;
	char	bit;

	swith = (sizeof(char) * 8) - 1;
	while (swith >= 0)
	{
		bit = (message >> swith) & 1;
		send_bit(pid, bit, 1);
		usleep(100);
		swith--;
	}
}

void	send_bit(pid_t pid, char bit, int flag)
{
	if (bit == 0)
	{
		if (kill(pid, SIGUSR1) == -1)
		{
			ft_putstr_fd("kill error\n", 2);
			exit(EXIT_FAILURE);
		}
	}
	else if (bit == 1)
	{
		if (kill(pid, SIGUSR2) == -1)
		{
			ft_putstr_fd("kill error\n", 2);
			exit(EXIT_FAILURE);
		}
	}
	if (flag != 0)
		pause();
}
