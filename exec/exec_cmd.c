/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acolonne <acolonne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 18:28:11 by acolonne          #+#    #+#             */
/*   Updated: 2025/05/23 16:15:44 by acolonne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	execute_cmd_process(t_cmd *cmd, t_minishell *minishell)
{
	int	code;

	code = 0;
	if (is_builtin(cmd))
	{
		code = exec_builtin(cmd, minishell);
		free_minishell(minishell);
		exit(code);
	}
	else if (cmd->cmd_path && check_access(cmd->cmd_path))
	{
		if (execve(cmd->cmd_path, cmd->arg, minishell->env) == -1)
		{
			perror("command error");
			free_minishell(minishell);
			exit (1);
		}
	}
}

int	command_process(t_cmd *cmd, t_minishell *minishell)
{
	int	check;

	check = 0;
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if ((cmd->infile && cmd->infile_fd < 0)
		|| (cmd->outfile && cmd->outfile_fd < 0))
		check = 1;
	if (check == 0)
	{
		execute_cmd_process(cmd, minishell);
		check_cmd_error(minishell, cmd);
	}
	free_minishell(minishell);
	exit (1);
}

int	do_cmd(t_minishell *minishell, t_cmd *cmd, int nb)
{
	int				pipefd[2];
	static int		prev_pipe;

	pipefd[0] = -1;
	pipefd[1] = -1;
	if (nb > 1)
	{
		if (pipe(pipefd) < 0)
			return (1);
	}
	if (cmd->cmd_nb == 1)
		prev_pipe = -1;
	cmd->child = fork();
	g_signal_pid = cmd->child;
	if (cmd->child < 0)
		return (close_two_fd(pipefd[0], pipefd[1]), 1);
	else if (cmd->child == 0)
	{
		dup_io(cmd, prev_pipe, pipefd, nb);
		command_process(cmd, minishell);
	}
	close_pipe(&prev_pipe, cmd, nb, pipefd);
	return (0);
}

int	wait_cmd(t_minishell *minishell, int nb, pid_t last_pid)
{
	int		i;
	int		status;
	pid_t	pid;

	i = 0;
	while (i < nb)
	{
		pid = waitpid(-1, &status, 0);
		if (pid == last_pid)
		{
			if (WIFEXITED(status))
				minishell->exit_code = WEXITSTATUS(status);
			else
				minishell->exit_code = 0;
		}
		i++;
	}
	return (0);
}

int	pipe_cmd(t_minishell *minishell, int nb)
{
	int		i;
	pid_t	last_pid;
	t_cmd	*tmp;

	i = 0;
	tmp = minishell->cmd;
	while (i < nb)
	{
		if (do_cmd(minishell, tmp, nb) == 1)
			return (1);
		if (tmp->cmd_nb == nb)
			last_pid = tmp->child;
		close_fds(tmp);
		tmp = tmp->next;
		i++;
	}
	wait_cmd(minishell, nb, last_pid);
	return (0);
}
