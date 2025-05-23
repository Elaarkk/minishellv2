/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acolonne <acolonne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 13:31:15 by aguilleu          #+#    #+#             */
/*   Updated: 2025/05/23 15:46:22 by acolonne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	close_two_fd(int fd1, int fd2)
{
	if (fd1 > -1)
		close(fd1);
	if (fd2 > -1)
		close(fd2);
	return (0);
}

void	close_fds(t_cmd *cmd)
{
	t_cmd	*tmp;

	tmp = cmd;
	if (tmp->infile)
	{
		if (tmp->infile_fd > -1)
			close(tmp->infile_fd);
	}
	if (tmp->outfile)
	{
		if (tmp->outfile_fd > -1)
			close(tmp->outfile_fd);
	}
}

int	check_access(char *path)
{
	if ((access(path, F_OK) == 0) && (access(path, X_OK) == 0))
		return (1);
	return (0);
}

void	check_cmd_error(t_minishell *minishell, t_cmd *cmd)
{
	if (!cmd->cmd_path && check_dir(cmd->cmd_name) == 0)
	{
		print_error(cmd->cmd_name);
		if (ft_strncmp(cmd->cmd_name, "./", 2) == 0)
			print_error(": No such file or directory\n");
		else
			print_error(": command not found\n");
		free_minishell(minishell);
		exit(127);
	}
	if (check_access(cmd->cmd_path) == 0)
	{
		print_error(cmd->cmd_path);
		free_minishell(minishell);
		perror (" ");
		exit (126);
	}
}

void	close_pipe(int *prev_pipe, t_cmd *cmd, int nb, int pipefd[2])
{
	if ((*prev_pipe) != -1)
		close((*prev_pipe));
	if (cmd->cmd_nb < nb)
		(*prev_pipe) = pipefd[0];
	if (pipefd[1] != -1)
		close(pipefd[1]);
	if (cmd->cmd_nb == nb && (*prev_pipe) != -1)
	{
		close(pipefd[0]);
		close((*prev_pipe));
	}
}
