/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acolonne <acolonne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 13:32:53 by aguilleu          #+#    #+#             */
/*   Updated: 2025/05/23 16:24:52 by acolonne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	dup_io(t_cmd *cmd, int prev_pipe, int pipefd[2], int nb)
{
	if (cmd->infile && cmd->infile_fd > -1)
	{
		dup2(cmd->infile_fd, 0);
		close(cmd->infile_fd);
	}
	else if (cmd->infile == 0 && prev_pipe != -1)
		dup2(prev_pipe, 0);
	if (cmd->outfile && cmd->outfile_fd > -1)
	{
		dup2(cmd->outfile_fd, 1);
		close(cmd->outfile_fd);
	}
	else if (cmd->outfile == 0 && cmd->cmd_nb != nb && nb > 1)
		dup2(pipefd[1], 1);
	if (pipefd[0] != -1)
		close(pipefd[0]);
	if (pipefd[1] != -1)
		close(pipefd[1]);
	if (prev_pipe != -1)
		close(prev_pipe);
}

int	check_builtin(t_cmd *cmd, t_minishell *minishell)
{
	int	check;
	int	code;

	check = -1;
	code = 0;
	if (cmd->outfile && cmd->outfile_fd > -1)
	{
		check = dup2(1, 1);
		if (check == -1)
			return (0);
		if (dup2(cmd->outfile_fd, 1) == -1)
		{
			close(check);
			return (0);
		}
	}
	code = exec_builtin(cmd, minishell);
	if (cmd->outfile && cmd->outfile_fd > -1)
	{
		dup2(check, 1);
		close(check);
	}
	return (code);
}

int	exec_builtin(t_cmd *cmd1, t_minishell *minishell)
{
	char	*cmd;
	int		code;

	code = 0;
	cmd = cmd1->arg[0];
	if (!ft_strcmp("echo", cmd))
		code = ft_echo(cmd1);
	else if (!ft_strcmp("env", cmd))
		code = ft_env(minishell->env);
	else if (!ft_strcmp("cd", cmd))
		code = ft_cd(cmd1, minishell->env);
	else if (!ft_strcmp("pwd", cmd))
		code = ft_pwd(cmd1);
	else if (!ft_strcmp("export", cmd))
		code = ft_export(cmd1, &minishell->env);
	else if (!ft_strcmp("unset", cmd))
		code = ft_unset(cmd1, &minishell->env);
	else if (!ft_strcmp("exit", cmd))
		code = ft_exit(cmd1, minishell);
	return (code);
}

void	exec_cmd(t_minishell *minishell)
{
	t_cmd	*tmp;
	int		i;

	tmp = minishell->cmd;
	i = 0;
	while (tmp)
	{
		i++;
		tmp->cmd_nb = i;
		tmp = tmp->next;
	}
	tmp = minishell->cmd;
	if (i == 1 && is_builtin(minishell->cmd) && !minishell->cmd->next
		&& (!ft_strcmp("exit", tmp->arg[0]) || !ft_strcmp("cd", tmp->arg[0])
			|| (!ft_strcmp("export", tmp->arg[0]))
			|| (!ft_strcmp("unset", tmp->arg[0]))))
		minishell->exit_code = check_builtin(tmp, minishell);
	else
	{
		if (pipe_cmd(minishell, i) == 1)
		{
			free_minishell(minishell);
			exit(0);
		}
	}
}
