/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyoon <gyoon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 16:24:34 by gyoon             #+#    #+#             */
/*   Updated: 2023/01/30 15:20:09 by gyoon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"
#include "libft.h"
#include <signal.h>

void	handler(int sig, siginfo_t *info, void *v)
{
	static char	ch;
	static char	bit;

	(void) v;
	if (sig == SIGUSR1)
		ch |= 0x01 << bit;
	if (++bit == 8)
	{
		ft_putchar_fd(ch, 1);
		ch = 0;
		bit = 0;
	}
	kill(info->si_pid, sig);
}

t_server_data	*get_server_data(void)
{
	static t_server_data	sdata;

	return (&sdata);
}

void	init_server(void)
{
	get_server_data()->act.sa_sigaction = handler;
	sigemptyset(&get_server_data()->act.sa_mask);
	sidaddset(&get_server_data()->act.sa_mask, SIGUSR1);
	sidaddset(&get_server_data()->act.sa_mask, SIGUSR2);
	get_server_data()->act.sa_flags = SA_RESTART | SA_SIGINFO;
	get_server_data()->s_pid = getpid();


}

int	main(void)
{
	init_server();
	ft_printf("Server Process ID : %d\n", get_server_data()->s_pid);
	sigaction(SIGUSR1, &get_server_data()->act, FT_NULL);
	sigaction(SIGUSR2, &get_server_data()->act, FT_NULL);
	while (1)
		;
	return (0);
}
