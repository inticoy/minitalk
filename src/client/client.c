/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyoon <gyoon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 16:24:31 by gyoon             #+#    #+#             */
/*   Updated: 2023/01/29 22:49:00 by gyoon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"
#include "libft.h"
#include <signal.h>
#include <unistd.h>

volatile sig_atomic_t	ack;

void	handler(int sig, siginfo_t *info, void *v)
{
	(void) sig;
	(void) info;
	(void) v;
	if (!ack)
		ack = 1;
	/* if (sig == SIGUSR1)
		ack = 1;
	else if (sig == SIGUSR2)
		ack = 0;
	else
		ack = -1; */
}

int	main(int argc, char **argv)
{
	t_sigaction	sigact;
	pid_t		pid;

	if (argc != 3)
		raise_exception("execution must be './client [pid] [msg]'\n");
	pid = ft_atoi(argv[1]);
	sigact.sa_sigaction = handler;
	sigemptyset(&sigact.sa_mask);
	sigaddset(&sigact.sa_mask, SIGUSR1);
	sigaddset(&sigact.sa_mask, SIGUSR2);
	sigact.sa_flags = SA_RESTART | SA_SIGINFO;
	sigaction(SIGUSR1, &sigact, FT_NULL);
	sigaction(SIGUSR2, &sigact, FT_NULL);
	ack = 0;
	unsigned int i = 0;
	while (i < ft_strlen(argv[2]))
	{
		int j = 0;
		char c = argv[2][i];
		while (j < 8)
		{
			usleep(20);
			if (c & 0x01)
			{
				kill(pid, SIGUSR1);
				while (ack != 1)
					;
			}
			else
			{
				kill(pid, SIGUSR2);
				while (ack != 1)
					;
			}
			ack = 0;
			c >>= 1;
			j++;
		}
		i++;
	}
	return (0);
}
