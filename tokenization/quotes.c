/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguilleu <aguilleu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 15:59:03 by aguilleu          #+#    #+#             */
/*   Updated: 2025/05/20 15:07:57 by aguilleu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_quote(char c)
{
	if (c == 34 || c == 39)
		return (1);
	return (0);
}

void	update_quote_state_open(char c, int *d, int *s)
{
	if (c == 34 && *s == 0)
		*d = 1;
	else if (c == 39 && *d == 0)
		*s = 1;
}

void	update_quote_state_close(char c, int *d, int *s)
{
	if (c == 39 && *d == 0 && *s == 1)
		*s = 0;
	else if (c == 34 && *s == 0 && *d == 1)
		*d = 0;
}

void	handle_char(char *prompt, int *i, int *d, int *s)
{
	char	c;

	c = prompt[*i];
	if (is_quote(c) && *d == 0 && *s == 0)
	{
		update_quote_state_open(c, d, s);
		if (prompt[*i])
			(*i)++;
	}
	else if (is_quote(c))
	{
		update_quote_state_close(c, d, s);
		if (prompt[*i])
			(*i)++;
	}
	else if (prompt[*i] != 34 && prompt[*i] != 39)
		(*i)++;
}

int	check_quotes(char *prompt)
{
	int	i;
	int	d;
	int	s;

	i = 0;
	d = 0;
	s = 0;
	if (!prompt)
	{
		printf("exit\n");
		return (0);
	}
	while (prompt && prompt[i])
		handle_char(prompt, &i, &d, &s);
	if (d == 1 || s == 1)
	{
		printf("Error : opened quotes\n");
		return (0);
	}
	return (1);
}
