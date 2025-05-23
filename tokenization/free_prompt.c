/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_prompt.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguilleu <aguilleu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 17:38:54 by acolonne          #+#    #+#             */
/*   Updated: 2025/05/20 15:55:21 by aguilleu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_prompt(t_prompt **lst)
{
	t_prompt	*tmp;
	int			i;

	i = 0;
	if (!(*lst))
		return ;
	while (*lst)
	{
		i++;
		tmp = *lst;
		(*lst) = (*lst)->next;
		free(tmp);
	}
}

void	free_prompt_content(t_prompt **lst)
{
	t_prompt	*tmp;

	tmp = *lst;
	while (tmp)
	{
		if (tmp->text && tmp->token == NORMAL)
			free(tmp->text);
		tmp = tmp->next;
	}
}

void	free_all_prompt(t_prompt **lst)
{
	free_prompt_content(lst);
	free_prompt(lst);
}

void	exit_clean(int code, t_prompt **prompt)
{
	free_prompt_content(prompt);
	free_prompt(prompt);
	exit(code);
}
