/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acolonne <acolonne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 13:49:13 by aguilleu          #+#    #+#             */
/*   Updated: 2025/05/23 16:28:24 by acolonne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_dir(char	*path)
{
	struct stat	path_stat;

	if (stat (path, &path_stat) != 0)
		return (0);
	return (S_ISDIR(path_stat.st_mode));
}

char	*get_cmd(char *cmd)
{
	int		i;
	char	*cmd_cpy;

	if (!cmd)
		return (0);
	i = 0;
	cmd_cpy = copy_cmd(&cmd[i]);
	return (cmd_cpy);
}

char	*check_file(char *cmd, char *subpath)
{
	char		*path;
	struct stat	check;

	path = NULL;
	path = ft_strjoin(subpath, cmd);
	if (stat(path, &check) != -1)
		return (path);
	free(path);
	return (0);
}

char	*check_local(char *cmd1)
{
	char		*cmd;
	struct stat	check;

	cmd = get_cmd(cmd1);
	if (check_dir(cmd1) == 1)
	{
		free(cmd);
		print_error(cmd1);
		print_error(": is a directory\n");
		return (0);
	}
	if (cmd && (stat(cmd, &check) != -1))
		return (cmd);
	if (cmd)
		free(cmd);
	return (0);
}

void	error_cmd(char *cmd, char *cmd1)
{
	free(cmd);
	print_error(cmd1);
	print_error(": is a directory\n");
}
