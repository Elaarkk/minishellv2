/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_operand.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguilleu <aguilleu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 13:43:53 by aguilleu          #+#    #+#             */
/*   Updated: 2025/05/23 18:58:54 by aguilleu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	go_to_next_cmd(t_prompt *prompt, int *i)
{
	t_prompt	*tmp;

	tmp = prompt;
	while (tmp && tmp->token != PIPE)
	{
		*i = *i + 1;
		tmp = tmp->next;
	}
	return ;
}

void	input(t_cmd *tmp, t_prompt *prompt, t_minishell *minishell)
{
	if (tmp->infile == 1)
	{
		if (tmp->infile_fd != -1)
			close(tmp->infile_fd);
	}
	tmp->infile = 1;
	if (prompt->token == HEREDOC)
	{
		tmp->heredoc_expand = check_heredoc_quotes(prompt->next->text);
		remove_quotes_from_prompt(prompt->next);
		tmp->infile_fd = heredoc(prompt->next->text,
				minishell, tmp->heredoc_expand);
	}
	else
	{
		tmp->infile_fd = open(prompt->next->text, O_RDONLY, 0644);
		if (tmp->infile_fd < 0)
		{
			perror("infile");
			minishell->exit_code = 1;
			prompt->is_error = 1;
		}
	}
}

void	output(t_cmd *tmp, t_prompt *prompt, t_minishell *minishell)
{
	if (tmp->outfile == 1)
	{
		if (tmp->outfile_fd != -1)
			close(tmp->outfile_fd);
	}
	tmp->outfile = 1;
	if (prompt->token == APPEND)
		tmp->outfile_fd = open(prompt->next->text,
				O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		tmp->outfile_fd = open(prompt->next->text,
				O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (tmp->outfile_fd < 0)
	{
		perror("outfile");
		minishell->exit_code = 1;
		prompt->is_error = 1;
	}
}

void	cmd_operand(t_prompt *prompt, t_cmd **cmd,
	int *i, t_minishell *minishell)
{
	t_cmd	*tmp;

	tmp = *cmd;
	if (prompt->token == INPUT || prompt->token == HEREDOC)
		input(tmp, prompt, minishell);
	else if (prompt->token == OUTPUT || prompt->token == APPEND)
		output(tmp, prompt, minishell);
	if (prompt->is_error == 1)
		go_to_next_cmd(prompt, i);
	else
		*i = *i + 2;
}

int	check_empty(t_prompt *prompt)
{
	int	i;

	i = 0;
	while (prompt)
	{
		if (!prompt->text)
			i++;
		prompt = prompt->next;
	}
	return (i);
}
