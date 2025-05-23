/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_create_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguilleu <aguilleu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 19:49:00 by aguilleu          #+#    #+#             */
/*   Updated: 2025/05/23 19:55:09 by aguilleu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_cmd	*handle_new_cmd_node(t_cmd **cmd)
{
	t_cmd	*new;

	new = create_cmd_node();
	if (!new)
	{
		free_all_cmd(cmd);
		return (0);
	}
	return (new);
}

void	process_cmd_loop(t_prompt **prompt, t_cmd **tmp,
			int *i, t_minishell *ms)
{
	int			j;
	t_prompt	*start;

	j = 0;
	start = *prompt;
	add_cmd(start, tmp, i, ms);
	while (*prompt && j < *i)
	{
		*prompt = (*prompt)->next;
		j++;
	}
}
