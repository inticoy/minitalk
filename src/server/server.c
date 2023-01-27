/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyoon <gyoon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 16:24:34 by gyoon             #+#    #+#             */
/*   Updated: 2023/01/27 15:01:17 by gyoon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"
#include "libft.h"
#include <signal.h>

typedef struct sigaction	t_sigaction;

void	handler(int sig)
{
	static char	ch;
	char		test;
	static char	bit;
	static char count;

	test = 0;
	if (sig == SIGUSR1)
		test = 0x01 << bit;
	ch |= test;
	bit++;
	if (bit == 8)
	{
		write(1, &ch, 1);
		ch = 0;
		bit = 0;
	}
	count++;
	//ft_printf("%d\n", count);
}

int	main(void)
{
	t_sigaction	sigact;
	pid_t		pid;

	pid = getpid();
	ft_printf("Server Process ID : %d\n", pid);
	ft_printf("%x", 'A');
	sigact.sa_handler = handler;
	sigemptyset(&sigact.sa_mask);
	sigact.sa_mask |= SIGUSR1 | SIGUSR2;
	sigact.sa_flags |= SA_RESTART | SA_SIGINFO;
	sigaction(SIGUSR1, &sigact, FT_NULL);
	sigaction(SIGUSR2, &sigact, FT_NULL);
	while (1)
		;
	return (0);
}
