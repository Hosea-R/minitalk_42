/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrazanad <mrazanad@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 13:33:01 by mrazanad          #+#    #+#             */
/*   Updated: 2024/08/07 17:28:11 by mrazanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static void	server_message_finished(t_minitalk *t_server, int *i,
		pid_t client_pid)
{
	if (t_server->bit == 8)
	{
		t_server->mess[*i] = t_server->data;
		(*i)++;
		if (t_server->data == '\0')
		{
			ft_putstr_fd(t_server->mess, 1);
			free(t_server->mess);
			t_server->mess = NULL;
			*i = 0;
			send_bit(client_pid, 1, 0);
		}
		t_server->bit = 0;
		t_server->data = 0;
	}
}

static void	server_handler(int number, siginfo_t *info, void *ucontext)
{
	static t_minitalk	t_server = {0, 0, 0, NULL};
	static int			i = 0;

	usleep(100);
	(void)ucontext;
	if (t_server.bit == 0 && t_server.mess == NULL)
	{
		t_server.mess = ft_calloc(1024, sizeof(char));
		if (!t_server.mess)
		{
			ft_putstr_fd("\e[31m## error - ft_calloc() ##\n\e[0m", 2);
			exit(EXIT_FAILURE);
		}
	}
	if (number == SIGUSR2)
		t_server.data |= 1 << (7 - t_server.bit);
	t_server.bit++;
	server_message_finished(&t_server, &i, info->si_pid);
	send_bit(info->si_pid, 0, 0);
}

int	main(void)
{
	struct sigaction	s_server;

	sigemptyset(&s_server.sa_mask);
	s_server.sa_sigaction = server_handler;
	s_server.sa_flags = SA_SIGINFO | SA_RESTART;
	setup_signal_handler(&s_server);
	ft_putstr_fd("\e[92mserver [PID = ", 1);
	ft_putnbr_fd(getpid(), 1);
	ft_putstr_fd("]\n\e[0m", 1);
	while (1)
		pause();
	return (EXIT_SUCCESS);
}
