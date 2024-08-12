/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrazanad <mrazanad@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 13:32:52 by mrazanad          #+#    #+#             */
/*   Updated: 2024/08/09 09:09:24 by mrazanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static void	client_handler(int sig)
{
	if (sig == SIGUSR1)
		return ;
	else if (sig == SIGUSR2)
	{
		return ;
		exit(EXIT_SUCCESS);
	}
}

static void	c_send_message(int pid_server, char *message)
{
	int	i;

	i = 0;
	while (message[i] != '\0')
		send_char_message(pid_server, message[i++]);
	send_char_message(pid_server, '\0');
}

int	main(int argc, char **argv)
{
	struct sigaction	s_client;
	int					pid_server;

	sigemptyset(&s_client.sa_mask);
	s_client.sa_flags = SA_RESTART;
	s_client.sa_handler = client_handler;
	setup_signal_handler(&s_client);
	if (argc != 3)
	{
		ft_putstr_fd("Usage: ./client [PID_SERVER] [MESSAGE]\n", 2);
		return (EXIT_FAILURE);
	}
	pid_server = ft_atoi(argv[1]);
	if (pid_server <= 0)
	{
		ft_putstr_fd("Error: Invalid PID_SERVER\n", 2);
		return (EXIT_FAILURE);
	}
	if (kill(pid_server, 0) == -1)
	{
		ft_putstr_fd("Error: Could not send signal to PID_SERVER\n", 2);
		return (EXIT_FAILURE);
	}
	c_send_message(pid_server, argv[2]);
	return (EXIT_SUCCESS);
}
