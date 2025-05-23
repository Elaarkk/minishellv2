/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_operand_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguilleu <aguilleu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 13:45:25 by aguilleu          #+#    #+#             */
/*   Updated: 2025/05/23 19:01:54 by aguilleu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	count_line(t_prompt *tmp)
{
	int	j;

	j = 0;
	while (tmp && tmp->token && tmp->token != PIPE)
	{
		if (tmp->token == NORMAL && tmp->text
			&& (!tmp->prev
				|| (tmp->prev && (tmp->prev->token == NORMAL
						|| tmp->prev->token == PIPE))))
			j++;
		tmp = tmp->next;
	}
	return (j);
}

void	increment_cmd(t_prompt **prompt, int *i, int *j)
{
	while (*prompt && (*j < *i))
	{
		*prompt = (*prompt)->next;
		(*j)++;
	}
}

int	void_case(char *content)
{
	int			i;

	i = 0;
	if (!content)
		return (0);
	i = ft_strlen(content);
	if (i >= 2 && content[0] == '$')
	{
		if (content[1] == 33 || (content[1] > 34 && content[1] < 39))
			return (1);
		if (content[1] > 39 && content[1] <= 47)
			return (1);
		if (content[1] == 58 || content[1] == 59 || content[1] == '=')
			return (1);
		if (content[1] >= 91 && content[1] <= 93)
			return (1);
		if (content[1] >= 123 && content[1] <= 126)
			return (1);
	}
	return (0);
}

void	check_expand(t_minishell *minishell)
{
	t_prompt	*tmp;

	tmp = minishell->prompt;
	while (tmp)
	{
		if (tmp->token && ((!tmp->prev) || (tmp->prev && tmp->prev != HEREDOC)))
		{
			if (tmp->token == NORMAL && tmp->text
				&& (!tmp->prev || tmp->prev->token != HEREDOC))
				remove_quotes_from_prompt(tmp);
		}
		tmp = tmp->next;
	}
}

int	check_operand_error(t_prompt *prompt, t_minishell *minishell)
{
	t_prompt	*tmp;

	tmp = prompt;
	while (tmp)
	{
		if ((tmp->token == HEREDOC || tmp->token == APPEND
				|| tmp->token == INPUT
				|| tmp->token == OUTPUT) && ((tmp->next == 0)
				|| (tmp->next->token != NORMAL)))
		{
			print_error("bash: syntax error near unexpected token\n");
			minishell->exit_code = 2;
			return (1);
		}
		if (tmp->token == PIPE && ((!tmp->next
					|| ((tmp->next && (tmp->next->token == PIPE))
						|| !tmp->prev))))
		{
			print_error("bash: syntax error near unexpected token\n");
			minishell->exit_code = 2;
			return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}
