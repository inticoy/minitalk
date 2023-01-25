/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyoon <gyoon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 16:24:31 by gyoon             #+#    #+#             */
/*   Updated: 2023/01/25 22:23:52 by gyoon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"
#include <signal.h>
#include <stdio.h>

int	main(int argc, char **argv)
{
	printf("%d\n", argc);
	printf("%s\n", argv[2]);
	return (0);
}
