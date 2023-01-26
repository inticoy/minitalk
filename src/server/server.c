/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyoon <gyoon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 16:24:34 by gyoon             #+#    #+#             */
/*   Updated: 2023/01/26 17:22:23 by gyoon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"
#include <signal.h>

typedef struct sigaction	t_sigaction;

void	handler(int sig)
{
	static char	ch;
	static char	bit;

	if (sig == SIGUSR1)
		ch++;
	ch << 1;
	bit++;
	if (bit == 8)
	{
		write(1, &ch, 1);
		ch = 0;
		bit = 0;
	}

}

int	main(void)
{
	t_sigaction	sigact;
	pid_t		pid;

	pid = getpid();
	printf("Server Process ID : %d\n", pid);

	
	while (1)
	{}
	return (0);
}

