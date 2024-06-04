/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opanikov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 18:17:12 by opanikov          #+#    #+#             */
/*   Updated: 2024/04/03 18:52:04 by opanikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include "Libft/libft.h"

void	ft_sig_1(int i, siginfo_t *info, void *context)
{
	static unsigned char	bit;
	static unsigned int		count;
	static unsigned int		pid;

	(void)context;
	bit <<= 1;
	if (i == SIGUSR1)
		bit |= 1;
	count++;
	if (count == 8)
	{
		write (1, &bit, 1);
		count = 0;
		bit = 0;
	}
	if (info->si_pid != 0)
		pid = info->si_pid;
	kill (pid, SIGUSR1);
}

int	main(void)
{
	int					id_server;
	struct sigaction	sa;

	id_server = getpid();
	ft_putnbr_fd(id_server, 1);
	sa.sa_sigaction = ft_sig_1;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	while (1)
		;
	return (0);
}
