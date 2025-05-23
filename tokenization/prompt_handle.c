/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_handle.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguilleu <aguilleu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 13:36:05 by aguilleu          #+#    #+#             */
/*   Updated: 2025/05/23 13:36:47 by aguilleu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	update_parsing(char *content, int *i, int *token)
{
	*i += skip_spaces(&content[*i]);
	if (content[*i] == '\0')
		return ;
	*token = identify_token(&content[*i]);
}

static char	*get_token_text(char *content, int token, int prev_token, int *len)
{
	if (token == NORMAL && prev_token != HEREDOC)
		return (token_normal(content, len));
	else if (token == NORMAL && prev_token == HEREDOC)
		return (token_normal_heredoc(content, len));
	else
	{
		*len = ft_strlen(token_operand(token));
		return (token_operand(token));
	}
}

t_prompt	*create_and_add_prompt(t_prompt *prompt, char *text, int token)
{
	t_prompt	*new;

	if (!prompt)
		return (create_prompt(text, token, 0));
	new = create_prompt(text, token, &prompt);
	ft_lstadd_back(&prompt, new);
	return (prompt);
}

t_prompt	*process_prompt_loop(char *content, int i, t_prompt *prompt)
{
	int			token;
	int			len;
	int			prev_token;
	char		*text;

	prev_token = -1;
	while (content && content[i])
	{
		update_parsing(content, &i, &token);
		if (content[i] == '\0')
			break ;
		text = get_token_text(&content[i], token, prev_token, &len);
		prompt = create_and_add_prompt(prompt, text, token);
		i += len;
		i += skip_spaces(&content[i]);
		prev_token = token;
	}
	return (prompt);
}

t_prompt	*cut_prompt(char *content)
{
	int			i;
	t_prompt	*prompt;

	i = 0;
	prompt = 0;
	return (process_prompt_loop(content, i, prompt));
}
