/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acolonne <acolonne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 17:18:38 by aguilleu          #+#    #+#             */
/*   Updated: 2025/05/23 16:30:21 by acolonne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	is_numeric(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	is_too_long(char *str)
{
	int		neg;
	char	*num;
	int		len;

	neg = 0;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			neg = 1;
		str++;
	}
	while (*str == '0')
		str++;
	num = str;
	len = ft_strlen(num);
	if (len > 19)
		return (1);
	if (len < 19)
		return (0);
	if (neg)
		return (ft_strcmp(num, "9223372036854775808") > 0);
	return (ft_strcmp(num, "9223372036854775807") > 0);
}

void	good_exit(t_minishell *minishell, int code)
{
	rl_clear_history();
	free_minishell(minishell);
	printf("exit\n");
	exit(code);
}

int	ft_exit(t_cmd *cmd, t_minishell *minishell)
{
	char		*arg_code;
	long long	exit_code;

	if (cmd->arg[1])
	{
		arg_code = cmd->arg[1];
		if (!is_numeric(arg_code) || is_too_long(arg_code))
		{
			printf("bash: exit: %s: numeric argument required\n", arg_code);
			good_exit(minishell, 255);
		}
		if (cmd->arg[2])
		{
			printf("bash: exit: too many arguments\n");
			good_exit(minishell, 255);
		}
		exit_code = ft_atoll(arg_code);
		if (exit_code < 0 || exit_code > 255)
			good_exit(minishell, 255);
		good_exit(minishell, exit_code);
	}
	good_exit(minishell, 0);
	return (0);
}
