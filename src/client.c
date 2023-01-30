/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyoon <gyoon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 16:24:31 by gyoon             #+#    #+#             */
/*   Updated: 2023/01/30 17:34:45 by gyoon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"
#include "libft.h"
#include <signal.h>
#include <unistd.h>

volatile sig_atomic_t	g_ack;

void	handler(int sig, siginfo_t *info, void *v)
{
	(void) sig;
	(void) info;
	(void) v;
	if (!g_ack)
		g_ack = 1;
}

void	send_null(pid_t pid)
{
	int	i;

	i = 0;
	while (i < 8)
	{
		usleep(50);
		kill(pid, SIGUSR2);
		while (g_ack != 1)
			;
		g_ack = 0;
		i++;
	}
}

void	send_msg(pid_t pid, char *msg)
{
	const size_t	mlen = ft_strlen(msg);
	size_t			i;
	size_t			j;
	char			c;

	i = 0;
	while (i < mlen)
	{
		j = 0;
		c = msg[i];
		while (j < 8)
		{
			usleep(50);
			if (c & 0x01)
				kill(pid, SIGUSR1);
			else
				kill(pid, SIGUSR2);
			while (g_ack != 1)
				;
			g_ack = 0;
			c >>= 1;
			j++;
		}
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_sigaction	act;
	pid_t		pid;

	if (argc != 3)
		raise_exception("execution must be './client [pid] [msg]'\n");
	pid = ft_atoi(argv[1]);
	act.sa_sigaction = handler;
	sigemptyset(&act.sa_mask);
	sigaddset(&act.sa_mask, SIGUSR1);
	sigaddset(&act.sa_mask, SIGUSR2);
	act.sa_flags = SA_RESTART | SA_SIGINFO;
	sigaction(SIGUSR1, &act, FT_NULL);
	sigaction(SIGUSR2, &act, FT_NULL);
	send_msg(pid, argv[2]);
	send_null(pid);
	ft_printf("Msg sent to [%d] successfully.", pid);
	return (0);
}
