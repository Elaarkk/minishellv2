/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguilleu <aguilleu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 15:27:18 by acolonne          #+#    #+#             */
/*   Updated: 2025/05/23 18:56:56 by aguilleu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*token_operand(int token)
{
	char	*text;

	if (token == HEREDOC)
		text = "<<";
	if (token == APPEND)
		text = ">>";
	if (token == INPUT)
		text = "<";
	if (token == OUTPUT)
		text = ">";
	if (token == PIPE)
		text = "|";
	return (text);
}

char	*token_normal_heredoc(char *content, int *len)
{
	int		i;
	char	*text;

	i = 0;
	*len = 0;
	text = malloc((ft_strlen(content)) + 1);
	if (!text)
		return (0);
	while (content[*len] && content[*len] != ' '
		&& content[*len] != '\t' && content[*len] != '<'
		&& content[*len] != '>' && content[*len] != '|')
	{
			text[i++] = content[(*len)++];
	}
	text[i] = '\0';
	return (text);
}

char	*cpy_token_normal(int *len, char *content, char *text)
{
	char	quote;
	int		i;

	i = 0;
	while (content[*len] && content[*len] != ' '
		&& content[*len] != '\t' && content[*len] != '<'
		&& content[*len] != '>' && content[*len] != '|')
	{
		if (content[*len] == 39 || content[*len] == 34)
		{
			quote = content[*len];
			text[i++] = content[(*len)++];
			while (content[*len] && content[*len] != quote)
				text[i++] = content[(*len)++];
			if (content[*len] == quote)
				text[i++] = content[(*len)++];
		}
		else
			text[i++] = content[(*len)++];
	}
	text[i] = '\0';
	return (text);
}

char	*token_normal(char *content, int *len)
{
	char	*text;

	*len = 0;
	text = malloc(ft_strlen(content) + 1);
	if (!text)
		return (NULL);
	text = cpy_token_normal(len, content, text);
	return (text);
}

int	identify_token(char *prompt)
{
	if (ft_strncmp(prompt, "<<", 2) == 0)
		return (HEREDOC);
	if (ft_strncmp(prompt, ">>", 2) == 0)
		return (APPEND);
	if (ft_strncmp(prompt, "<", 1) == 0)
		return (INPUT);
	if (ft_strncmp(prompt, ">", 1) == 0)
		return (OUTPUT);
	if (ft_strncmp(prompt, "|", 1) == 0)
		return (PIPE);
	else
		return (NORMAL);
}
