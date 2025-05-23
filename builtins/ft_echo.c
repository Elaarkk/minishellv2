/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acolonne <acolonne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 16:01:03 by aguilleu          #+#    #+#             */
/*   Updated: 2025/05/22 18:03:29 by acolonne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_n_flag(char *s)
{
	int	i;

	i = 0;
	if (!s || s[0] != '-' || s[1] != 'n')
		return (0);
	i = 2;
	while (s[i])
	{
		if (s[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

int	ft_echo(t_cmd *cmd)
{
	int	i;
	int	print_nl;

	i = 1;
	print_nl = 1;
	while (cmd->arg[i] && is_n_flag(cmd->arg[i]))
	{
		print_nl = 0;
		i++;
	}
	while (cmd->arg[i])
	{
		ft_putstr_fd(cmd->arg[i], 1);
		if (cmd->arg[i + 1])
			ft_putstr_fd(" ", 1);
		i++;
	}
	if (print_nl)
		ft_putstr_fd("\n", 1);
	return (0);
}
