/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acolonne <acolonne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 18:26:10 by aguilleu          #+#    #+#             */
/*   Updated: 2025/05/23 16:22:25 by acolonne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	add_new_env_variable(char *var, char *value, char ***env)
{
	int		i;
	int		len;
	char	**new_env;

	i = 0;
	len = 0;
	while ((*env) && (*env)[len])
		len++;
	new_env = malloc(sizeof(char *) * (len + 2));
	if (!new_env)
		return ;
	while (i < len)
	{
		new_env[i] = (*env)[i];
		i++;
	}
	new_env[i] = malloc(ft_strlen(var) + ft_strlen(value) + 2);
	if (!new_env[i])
		return ;
	ft_strlcpy(new_env[i], var, ft_strlen(var) + ft_strlen(value) + 2);
	ft_strlcat(new_env[i], "=", ft_strlen(var) + ft_strlen(value) + 2);
	ft_strlcat(new_env[i], value, ft_strlen(var) + ft_strlen(value) + 2);
	new_env[i + 1] = NULL;
	free(*env);
	*env = new_env;
}

void	update_env_variable(char *var, char *value, char ***env)
{
	int		j;
	char	*new_env_var;
	int		tot;

	tot = ft_strlen(var) + ft_strlen(value) + 2;
	j = 0;
	while ((*env)[j])
	{
		if (ft_strncmp((*env)[j], var, ft_strlen(var)) == 0
			&& (*env)[j][ft_strlen(var)] == '=')
		{
			free((*env)[j]);
			new_env_var = malloc(tot);
			if (!new_env_var)
				return ;
			ft_strlcpy(new_env_var, var, tot);
			ft_strlcat(new_env_var, "=", tot);
			ft_strlcat(new_env_var, value, tot);
			(*env)[j] = new_env_var;
			return ;
		}
		j++;
	}
	add_new_env_variable(var, value, env);
}

int	process_export_argument(char *arg, char ***env)
{
	char	*value;
	char	*var_copy;

	value = ft_strchr(arg, '=');
	if (value)
	{
		var_copy = ft_substr(arg, 0, value - arg);
		if (!is_valid_identifier(var_copy))
		{
			printf("bash: export: `%s': not a valid identifier\n", arg);
			free(var_copy);
			return (2);
		}
		value++;
		update_env_variable(var_copy, value, env);
		free(var_copy);
	}
	else
	{
		if (!is_valid_identifier(arg))
			printf("bash: export: `%s': not a valid identifier\n", arg);
		return (2);
	}
	return (0);
}

int	handle_export_argument(char *arg, char ***env)
{
	int	code;

	code = 0;
	if (arg[0] == '-' && ft_strlen(arg) > 1)
	{
		if (arg[1] == '-')
		{
			printf("bash: export: `%s': wrong option\n", "--");
			return (2);
		}
		else
		{
			printf("bash: export: `-%c': wrong option\n", arg[1]);
			return (2);
		}
	}
	if (arg[0] != '-')
		code = process_export_argument(arg, env);
	return (code);
}

int	ft_export(t_cmd *cmd1, char ***env)
{
	int	i;
	int	code;

	if (cmd1->arg[1] == NULL)
		return (2);
	i = 1;
	while (cmd1->arg[i])
	{
		code = handle_export_argument(cmd1->arg[i], env);
		i++;
	}
	return (code);
}
