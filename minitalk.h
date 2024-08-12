/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrazanad <mrazanad@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 13:33:12 by mrazanad          #+#    #+#             */
/*   Updated: 2024/08/09 15:57:25 by mrazanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# include "libft/libft.h"
# include <signal.h>
# include <stdlib.h>

typedef struct s_minitalk
{
	int		bit;
	int		data;
	int		flag;
	char	*mess;
}			t_minitalk;

void		setup_signal_handler(struct sigaction *sa);
void		send_char_message(pid_t pid, char message);
void		send_bit(pid_t pid, char bit, int flag);

#endif
