/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyoon <gyoon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 17:29:48 by gyoon             #+#    #+#             */
/*   Updated: 2023/01/30 15:08:31 by gyoon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_H
# define SERVER_H

# include "libft.h"
# include <unistd.h>
# include <signal.h>

typedef struct s_server_data
{
	struct sigaction	act;
	pid_t				s_pid;
	pid_t				c_pid;
	t_string			msg;
}	t_server_data;
#endif
