/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguilleu <aguilleu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 14:50:09 by acolonne          #+#    #+#             */
/*   Updated: 2025/05/23 13:57:48 by aguilleu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_prompt	*create_prompt(char *content, int token, t_prompt **first)
{
	t_prompt	*prompt;

	prompt = 0;
	prompt = malloc(sizeof(t_prompt));
	if (!prompt)
	{
		if (first && *first)
			exit_clean(1, first);
		else
			exit(1);
	}
	prompt->next = NULL;
	prompt->prev = NULL;
	prompt->expand = 1;
	prompt->is_error = 0;
	prompt->text = 0;
	prompt->text = content;
	prompt->token = token;
	return (prompt);
}

void	ft_lstadd_back(t_prompt **lst, t_prompt *new)
{
	t_prompt	*p;
	t_prompt	*previous;

	p = *lst;
	previous = p;
	if (!new)
		return ;
	if (*lst)
	{
		while (p->next)
		{
			p = p->next;
			previous = p;
		}
		p->next = new;
		p = new;
		new->prev = previous;
	}
	else
		*lst = new;
	return ;
}

long long	ft_atoll(const char *nptr)
{
	int	i;
	int	sign;
	int	nb;

	i = 0;
	nb = 0;
	sign = 1;
	while (nptr[i] == 32 || (nptr[i] >= 9 && nptr[i] <= 13))
		i++;
	if (nptr[i] == '+' || nptr[i] == '-')
	{
		if (nptr[i] == '-')
			sign = -sign;
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		nb = nb * 10 + (nptr[i] - 48);
		i++;
	}
	return (nb * sign);
}

void	handler(int num)
{
	if (num == SIGINT)
	{
		write(1, "\n", 1);
		if (g_signal_pid == 0)
		{
			rl_replace_line("", 0);
			rl_on_new_line();
			rl_redisplay();
		}
	}
}

void	free_split(int i, char **split)
{
	int	j;

	j = 0;
	if (!split)
		return ;
	while (j < i)
	{
		if (split[j])
			free(split[j]);
		j++;
	}
	free(split);
	return ;
}
