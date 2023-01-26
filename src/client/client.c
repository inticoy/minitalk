/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyoon <gyoon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 16:24:31 by gyoon             #+#    #+#             */
/*   Updated: 2023/01/26 21:13:50 by gyoon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"
#include <signal.h>

int	main(int argc, char **argv)
{
	if (!is_valid_argc(argc))
		raise_exception("execution must be './client [pid] [msg]'\n");
	ft_printf("%d\n", argc);
	ft_printf("%s\n", argv[2]);
	return (0);
}
