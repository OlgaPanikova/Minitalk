/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opanikov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 18:14:09 by opanikov          #+#    #+#             */
/*   Updated: 2024/04/03 18:38:07 by opanikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include "Libft/libft.h"

static int	g_sig_ser;

void	error_handling(int i)
{
	if (i == 0)
	{
		write (1, "Not enough arguments\n", 21);
		exit(EXIT_FAILURE);
	}
	else if (i == 1)
	{
		write (1, "There is no message\n", 20);
		exit(EXIT_FAILURE);
	}
	else if (i == 2)
	{
		write (1, "Invalid server ID\n", 18);
		exit(EXIT_FAILURE);
	}
}

void	send_bit(int i, int id)
{
	g_sig_ser = 0;
	if (i == 1)
		kill(id, SIGUSR1);
	else if (i == 0)
		kill(id, SIGUSR2);
	while (g_sig_ser != 1)
		;
}

void	send_letter_bits(char letter, int id)
{
	int		i;

	i = 8;
	while (i--)
		send_bit((letter >> i) & 1, id);
}

void	signal_handling(int s)
{
	g_sig_ser = 1;
	if (s == SIGUSR2)
		exit(0);
}

int	main(int argc, char **argv)
{
	int					id_server;
	char				*message;
	struct sigaction	sa;

	if (argc != 3)
		error_handling(0);
	message = argv[2];
	if (!message)
		error_handling(1);
	id_server = ft_atoi(argv[1]);
	if (id_server <= 0)
		error_handling(2);
	sa.sa_handler = signal_handling;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	while (*message)
	{
		send_letter_bits(*message, id_server);
		message++;
	}
	return (0);
}
