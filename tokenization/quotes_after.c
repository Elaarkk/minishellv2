/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_after.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguilleu <aguilleu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 13:38:50 by aguilleu          #+#    #+#             */
/*   Updated: 2025/05/23 13:50:29 by aguilleu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*text_without_quotes(t_prompt *prompt, int quote, char *new, int j)
{
	int	i;

	i = 0;
	while (prompt->text[i])
	{
		if ((prompt->text[i] == 39 || prompt->text[i] == 34))
		{
			if (quote == 0)
				quote = prompt->text[i];
			else if (quote == prompt->text[i])
				quote = 0;
			else
				new[j++] = prompt->text[i];
			i++;
		}
		else
			new[j++] = prompt->text[i++];
	}
	new[j] = '\0';
	return (new);
}

void	remove_quotes_from_prompt(t_prompt *prompt)
{
	char	*new;
	int		j;
	char	quote;

	j = 0;
	quote = 0;
	if (!prompt | !prompt->text)
		return ;
	new = malloc(ft_strlen(prompt->text) + 1);
	if (!new)
	{
		return ;
	}
	new = text_without_quotes(prompt, quote, new, j);
	free(prompt->text);
	prompt->text = new;
}

int	check_heredoc_quotes(char *text)
{
	int		i;

	i = 0;
	if (!text)
		return (0);
	while (text[i])
	{
		if (text[i] == '\'' || text[i] == '\"')
			return (0);
		i++;
	}
	return (1);
}

void	handle_double_quotes(t_minishell *minishell, char **text, int *i)
{
	(*i)++;
	while ((*text)[*i] && (*text)[*i] != '"')
	{
		if ((*text)[*i] == '$' && (*text)[*i + 1])
			expand_variable(minishell, text, i);
		else
			(*i)++;
	}
	if ((*text)[*i] == '"')
		(*i)++;
}
