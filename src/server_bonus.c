/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyoon <gyoon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 16:24:34 by gyoon             #+#    #+#             */
/*   Updated: 2023/01/30 16:03:58 by gyoon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server_bonus.h"
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
		if (!ch)
		{
			ft_printf("\nMsg received from [%d] successfully.\n", info->si_pid);
			ft_printf("Server Process ID : %d\n", getpid());
		}
		ch = 0;
		bit = 0;
	}
	kill(info->si_pid, sig);
}

int	main(int argc, char **argv)
{
	t_sigaction	act;
	pid_t		pid;

	(void) argv;
	if (argc != 1)
		raise_exception("execution must be './server'\n");
	pid = getpid();
	ft_printf("Server Process ID : %d\n", pid);
	act.sa_sigaction = handler;
	sigemptyset(&act.sa_mask);
	sigaddset(&act.sa_mask, SIGUSR1);
	sigaddset(&act.sa_mask, SIGUSR2);
	act.sa_flags = SA_RESTART | SA_SIGINFO;
	sigaction(SIGUSR1, &act, FT_NULL);
	sigaction(SIGUSR2, &act, FT_NULL);
	while (1)
		;
	return (0);
}
