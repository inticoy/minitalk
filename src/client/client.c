/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyoon <gyoon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 16:24:31 by gyoon             #+#    #+#             */
/*   Updated: 2023/01/27 15:01:11 by gyoon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"
#include "libft.h"
#include <signal.h>
#include <unistd.h>

void	handler(int sig)
{
	static char	ch;
	static char	bit;

	ch <<= 1;
	if (sig == SIGUSR1)
		ch |= 0x01;
	bit++;
	if (bit == 8)
	{
		write(1, &ch, 1);
		ch = 0;
		bit = 0;
	}
}

int	main(int argc, char **argv)
{
	t_sigaction	sigact;
	pid_t		pid;

	if (argc != 3)
		raise_exception("execution must be './client [pid] [msg]'\n");
	pid = ft_atoi(argv[1]);
	sigact.sa_handler = handler;
	sigemptyset(&sigact.sa_mask);
	sigact.sa_mask |= SIGUSR1 | SIGUSR2;
	sigact.sa_flags |= SA_RESTART | SA_SIGINFO;
	sigaction(SIGUSR1, &sigact, FT_NULL);
	sigaction(SIGUSR2, &sigact, FT_NULL);

	unsigned int i = 0;
	while (i < ft_strlen(argv[2]))
	{
		int j = 0;
		char c = argv[2][i];
		while (j < 8)
		{
			if (c & 0x01)
				kill(pid, SIGUSR1);
			else
				kill(pid, SIGUSR2);
			c >>= 1;
			j++;
			usleep(1000);
		}
		i++;
	}
	ft_printf("%d\n", ft_atoi(argv[1]));
	ft_printf("%s\n", argv[2]);
	return (0);
}
