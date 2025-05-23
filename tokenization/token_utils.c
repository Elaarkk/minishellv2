/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguilleu <aguilleu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 16:43:23 by acolonne          #+#    #+#             */
/*   Updated: 2025/05/23 19:49:39 by aguilleu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_cmd	*create_cmd_node(void)
{
	t_cmd	*cmd;

	cmd = 0;
	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (0);
	cmd->cmd_name = 0;
	cmd->cmd_path = 0;
	cmd->heredoc_expand = 0;
	cmd->arg = 0;
	cmd->infile = 0;
	cmd->infile_fd = -1;
	cmd->outfile = 0;
	cmd->outfile_fd = -1;
	cmd->append = 0;
	cmd->next = 0;
	cmd->error = 0;
	return (cmd);
}

int	is_empty(t_prompt *prompt)
{
	if (!prompt || !prompt->text)
		return (1);
	return (0);
}

void	increment_prompt(t_prompt **prompt, int k, int j)
{
	while ((*prompt) && k < j)
	{
		(*prompt) = (*prompt)->next;
		k++;
	}
}

void	ft_cmdadd_back(t_cmd **lst, t_cmd *new)
{
	t_cmd	*p;

	p = *lst;
	if (!new)
		return ;
	if (*lst)
	{
		while (p->next)
			p = p->next;
		p->next = new;
		p = new;
	}
	else
		*lst = new;
	return ;
}
