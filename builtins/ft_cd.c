/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguilleu <aguilleu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 19:00:00 by aguilleu          #+#    #+#             */
/*   Updated: 2025/05/20 15:01:48 by aguilleu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	update_env(char **env, char *key, char *val)
{
	int		i;
	int		klen;
	char	*entry;
	int		size;

	i = 0;
	klen = ft_strlen(key);
	size = klen + ft_strlen(val) + 2;
	while (env[i])
	{
		if (!ft_strncmp(env[i], key, klen) && env[i][klen] == '=')
		{
			entry = malloc(size);
			if (!entry)
				return (2);
			ft_strlcpy(entry, key, size);
			ft_strlcat(entry, "=", size);
			ft_strlcat(entry, val, size);
			free(env[i]);
			env[i] = entry;
			return (0);
		}
		i++;
	}
	return (2);
}

int	check_cd_args(t_cmd *cmd)
{
	char	*opt;
	int		count;
	int		i;

	count = 0;
	i = 0;
	while (cmd->arg && cmd->arg[i])
	{
		count++;
		i++;
	}
	if (count > 2)
		return (print_error("cd: too many arguments\n"), 0);
	if (count > 1)
	{
		opt = cmd->arg[1];
		if (opt[0] == '-' && opt[1])
		{
			printf("bash: cd: -%c: invalid option\n", opt[1]);
			return (0);
		}
	}
	return (1);
}

char	*get_cd_path(t_cmd *cmd, char **env)
{
	char	*arg;
	char	*val;

	arg = cmd->arg[1];
	if (!arg || !ft_strcmp(arg, "~"))
	{
		val = ft_getenv(env, "HOME");
		if (!val || !*val)
			return (print_error("No HOME\n"), NULL);
		return (val);
	}
	if (!ft_strcmp(arg, "-"))
	{
		val = ft_getenv(env, "OLDPWD");
		if (!val || !*val)
			return (print_error("No OLDPWD\n"), NULL);
		printf("%s\n", val);
		return (val);
	}
	return (arg);
}

char	*get_oldpwd(char **env)
{
	char	buf[1024];
	char	*pwd;

	pwd = NULL;
	if (getcwd(buf, 1024))
		pwd = ft_strdup(buf);
	else
	{
		pwd = ft_getenv(env, "PWD");
		if (pwd)
			pwd = ft_strdup(pwd);
		else
			pwd = ft_strdup("");
	}
	return (pwd);
}

int	ft_cd(t_cmd *cmd, char **env)
{
	char	*oldpwd;
	char	*path;
	char	*real;
	char	buf[1024];

	oldpwd = NULL;
	real = NULL;
	if (!check_cd_args(cmd))
		return (0);
	path = get_cd_path(cmd, env);
	if (!path)
		return (2);
	oldpwd = get_oldpwd(env);
	if (chdir(path) != 0)
	{
		real = realpath(path, NULL);
		if (!real || chdir(real) != 0)
			return (perror("cd"), free(oldpwd), free(real), 2);
	}
	update_env(env, "OLDPWD", oldpwd);
	if (getcwd(buf, 1024))
		update_env(env, "PWD", buf);
	free(oldpwd);
	free(real);
	return (0);
}
