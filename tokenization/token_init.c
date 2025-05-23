/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguilleu <aguilleu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 14:38:27 by acolonne          #+#    #+#             */
/*   Updated: 2025/05/23 19:53:34 by aguilleu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

extern pid_t	g_signal_pid;

char	*arg_assign(t_prompt *tmp, int *k, char **arg)
{
	if (tmp->token == NORMAL && tmp->text && (!tmp->prev
			|| (tmp->prev && (tmp->prev->token == NORMAL
					|| tmp->prev->token == PIPE))))
	{
		arg[*k] = malloc(ft_strlen(tmp->text) + 1);
		if (arg[*k] == 0)
		{
			free_split(*k, arg);
			return (0);
		}
		ft_strlcpy(arg[*k], tmp->text, ft_strlen(tmp->text) + 1);
		(*k)++;
	}
	return (arg[*k]);
}

char	**cmd_normal(t_prompt *prompt, t_cmd **cmd,
		int *i, t_minishell *minishell)
{
	t_prompt	*tmp;
	int			j;
	int			k;
	int			empty;
	char		**arg;

	j = 0;
	k = 0;
	empty = check_empty(prompt);
	tmp = prompt;
	j = count_line(tmp);
	arg = malloc((sizeof(char *) * (j + 1)));
	if (!arg)
		return (0);
	tmp = prompt;
	while (tmp && tmp->token && tmp->token != PIPE && k < j)
	{
		arg[k] = arg_assign(tmp, &k, arg);
		if (tmp->token != NORMAL && tmp->token != PIPE)
			cmd_operand(tmp, cmd, i, minishell);
		tmp = tmp->next;
	}
	*i += j + empty;
	arg[k] = NULL;
	return (arg);
}

void	add_cmd(t_prompt *prompt, t_cmd **cmd, int *i, t_minishell *minishell)
{
	t_cmd	*tmp;
	int		j;
	int		l;
	int		k;

	j = *i;
	l = j;
	k = 0;
	tmp = *cmd;
	while (prompt && prompt->token != PIPE)
	{
		if (prompt->token != NORMAL && prompt->token != PIPE)
			cmd_operand(prompt, cmd, i, minishell);
		if (prompt->token == NORMAL)
		{
			tmp->cmd_name = ft_strdup(prompt->text);
			tmp->arg = cmd_normal(prompt, cmd, i, minishell);
		}
		j = *i - l;
		while (prompt && k < j)
		{
			prompt = prompt->next;
			k++;
		}
	}
}

t_cmd	*create_cmd(t_prompt *prompt, t_minishell *minishell)
{
	t_cmd	*cmd;
	t_cmd	*tmp;
	int		i;

	cmd = create_cmd_node();
	if (!cmd)
		return (0);
	tmp = cmd;
	i = 0;
	while (prompt)
	{
		if (i != 0)
		{
			tmp = handle_new_cmd_node(&cmd);
			if (!tmp)
				return (0);
		}
		process_cmd_loop(&prompt, &tmp, &i, minishell);
		if (cmd != tmp)
			ft_cmdadd_back(&cmd, tmp);
		if (prompt && prompt->token == PIPE)
			prompt = prompt->next;
	}
	return (cmd);
}

int	analyse_prompt(t_minishell *minishell)
{
	if (check_operand_error(minishell->prompt, minishell) == 1)
	{
		free_all_prompt(&minishell->prompt);
		return (1);
	}
	check_expand(minishell);
	minishell->cmd = create_cmd(minishell->prompt, minishell);
	if (!minishell->cmd)
	{
		free_all_prompt(&minishell->prompt);
		return (1);
	}
	free_all_prompt(&minishell->prompt);
	exec_init(minishell, minishell->path);
	free_all_cmd(&minishell->cmd);
	return (0);
}
