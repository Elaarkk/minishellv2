/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguilleu <aguilleu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 02:09:11 by aguilleu          #+#    #+#             */
/*   Updated: 2025/05/23 13:50:03 by aguilleu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*copy_cmd(char *src)
{
	char	*cmd_copy;
	int		i;

	i = 0;
	if (!src)
		return (0);
	if (ft_strlen(src) == 0)
		return (0);
	cmd_copy = malloc(ft_strlen(src) + 1);
	if (!cmd_copy)
		return (0);
	while (src[i])
	{
		cmd_copy[i] = src[i];
		i++;
	}
	cmd_copy[i] = '\0';
	return (cmd_copy);
}

char	*check_cmd(char *cmd1, char **path)
{
	int		i;
	char	*cmd;
	char	*good_path;

	i = 0;
	cmd = get_cmd(cmd1);
	if (check_dir(cmd1) == 1)
	{
		error_cmd(cmd, cmd1);
		return (0);
	}
	while (path && path[i] && cmd)
	{
		good_path = check_file(cmd, path[i]);
		if (good_path)
		{
			if (cmd)
				free(cmd);
			return (good_path);
		}
		i++;
	}
	if (cmd)
		free(cmd);
	return (0);
}

int	is_builtin(t_cmd *cmd1)
{
	char	*cmd;

	if (!cmd1->cmd_name || !cmd1->arg)
		return (0);
	cmd = cmd1->arg[0];
	if (!cmd)
		return (0);
	if (!ft_strcmp("echo", cmd) || !ft_strcmp("cd", cmd)
		|| !ft_strcmp("pwd", cmd) || !ft_strcmp("export", cmd)
		|| !ft_strcmp("unset", cmd) || !ft_strcmp("env", cmd)
		|| !ft_strcmp("exit", cmd))
		return (1);
	return (0);
}

int	check_path(t_cmd *cmd)
{
	char	*command;
	int		i;

	command = 0;
	i = 0;
	if (cmd && cmd->cmd_name)
		command = cmd->cmd_name;
	while (command && command[i])
	{
		if (command[i] == '/')
			return (1);
		i++;
	}
	return (0);
}

void	exec_init(t_minishell *minishell, char **path)
{
	t_cmd	*tmp;
	int		is_a_path;

	tmp = minishell->cmd;
	is_a_path = 0;
	while (tmp)
	{
		is_a_path = check_path(tmp);
		if (path && tmp->cmd_name && tmp->arg && is_a_path == 0)
		{	
			if (!is_builtin(tmp))
				tmp->cmd_path = check_cmd(tmp->cmd_name, path);
		}
		else if (tmp->cmd_name && tmp->arg && is_a_path == 1)
		{
			if (!is_builtin(tmp))
				tmp->cmd_path = check_local(tmp->cmd_name);
		}
		tmp = tmp->next;
	}
	exec_cmd(minishell);
	return ;
}
