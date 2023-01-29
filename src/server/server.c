/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyoon <gyoon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 16:24:34 by gyoon             #+#    #+#             */
/*   Updated: 2023/01/29 22:17:31 by gyoon            ###   ########.fr       */
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
	else
		ch |= 0x00;
	if (++bit == 8)
	{
		ft_putchar_fd(ch, 1);
		ch = 0;
		bit = 0;
	}
	kill(info->si_pid, sig);
}

int	main(void)
{
	struct sigaction	sigact;
	pid_t				pid;

	pid = getpid();
	ft_printf("Server Process ID : %d\n", pid);
	sigact.sa_sigaction = handler;
	sigemptyset(&sigact.sa_mask);
	sigaddset(&sigact.sa_mask, SIGUSR1);
	sigaddset(&sigact.sa_mask, SIGUSR2);
	sigact.sa_flags = SA_RESTART | SA_SIGINFO;
	sigaction(SIGUSR1, &sigact, FT_NULL);
	sigaction(SIGUSR2, &sigact, FT_NULL);
	while (1)
		;
	return (0);
}
