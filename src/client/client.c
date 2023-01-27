/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyoon <gyoon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 16:24:31 by gyoon             #+#    #+#             */
/*   Updated: 2023/01/27 17:09:50 by gyoon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"
#include "libft.h"
#include <signal.h>
#include <unistd.h>

volatile sig_atomic_t	ack;

void	handler(int sig, siginfo_t *info, void *v)
{
	(void) info;
	(void) v;
	ft_printf("sig : %d\n", sig);
	if (sig == SIGUSR1)
		ack = 1;
	else if (sig == SIGUSR2)
		ack = 0;
	else
		ack = -1;
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
	sigact.sa_flags |= SA_RESTART | SA_SIGINFO;
	sigaction(SIGUSR1, &sigact, FT_NULL);
	sigaction(SIGUSR2, &sigact, FT_NULL);

	ack = -1;
	unsigned int i = 0;
	while (i < ft_strlen(argv[2]))
	{
		int j = 0;
		char c = argv[2][i];
		while (j < 8)
		{
			if (c & 0x01)
			{
				kill(pid, SIGUSR1);
				while (1)
					if (ack == 1)
						break ;
				ack = -1;
			}
			else
			{
				kill(pid, SIGUSR2);
				while (1)
					if (ack == 0)
						break ;
				ack = -1;
			}
			c >>= 1;
			j++;
		}
		i++;
	}

	ft_printf("%d\n", getpid());
	ft_printf("%d\n", ft_atoi(argv[1]));
	ft_printf("%s\n", argv[2]);
	return (0);
}
