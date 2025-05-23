/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguilleu <aguilleu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 17:39:18 by acolonne          #+#    #+#             */
/*   Updated: 2025/05/20 15:12:17 by aguilleu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_cmd(t_cmd **lst)
{
	t_cmd	*tmp;
	int		i;

	i = 0;
	if (!(*lst))
		return ;
	while (*lst)
	{
		i++;
		tmp = *lst;
		(*lst) = (*lst)->next;
		if (tmp)
			free(tmp);
	}
}

void	free_arg(char **arg)
{
	int	i;

	i = 0;
	if (!arg)
		return ;
	while (arg && arg[i])
	{
		if (arg[i])
			free(arg[i]);
		i++;
	}
	if (arg)
		free(arg);
}

void	free_cmd_content(t_cmd **lst)
{
	t_cmd	*tmp;

	tmp = *lst;
	while (tmp)
	{
		if (tmp->cmd_name)
			free(tmp->cmd_name);
		if (tmp->cmd_path)
			free(tmp->cmd_path);
		if (tmp->arg)
			free_arg(tmp->arg);
		tmp = tmp->next;
	}
}

void	free_all_cmd(t_cmd **lst)
{
	if (*lst)
		free_cmd_content(lst);
	if (*lst)
		free_cmd(lst);
}

void	exit_free_all(t_prompt **prompt, t_cmd **cmd, char *msg, int code)
{
	if (cmd && *cmd)
		free_all_cmd(cmd);
	if (prompt && *prompt)
		free_all_prompt(prompt);
	print_error(msg);
	exit(code);
}
