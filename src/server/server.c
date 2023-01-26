/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyoon <gyoon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 16:24:34 by gyoon             #+#    #+#             */
/*   Updated: 2023/01/26 20:29:36 by gyoon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"
#include "libft.h"
#include <signal.h>

typedef struct sigaction	t_sigaction;

void	handler(int sig)
{
	if (sig == SIGUSR1)
		ft_printf("catch USR1\n");
	else if (sig == SIGUSR2)
		ft_printf("catch USR2\n");

}

int	main(void)
{
	t_sigaction	sigact;
	pid_t		pid;

	pid = getpid();
	printf("Server Process ID : %d\n", pid);

	sigact.sa_handler = handler;
	sigemptyset(&sigact.sa_mask);
	sigact.sa_flags |= SA_RESTART;
	sigaction(SIGUSR1, &sigact, FT_NULL);
	sigaction(SIGUSR2, &sigact, FT_NULL);
	while (1)
		;
	return (0);
}


