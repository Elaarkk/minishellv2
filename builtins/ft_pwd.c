/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acolonne <acolonne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 17:54:37 by aguilleu          #+#    #+#             */
/*   Updated: 2025/05/23 16:10:33 by acolonne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_pwd(t_cmd *cmd)
{
	char	*cwd;
	char	*option;

	if (cmd->arg && cmd->arg[1])
	{
		option = cmd->arg[1];
		if (option[0] == '-' && option[1] != '\0')
		{
			printf("bash: pwd: -%c: invalid option\n", option[1]);
			return (2);
		}
	}
	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		perror("pwd: error message");
		return (2);
	}
	printf("%s\n", cwd);
	free(cwd);
	return (0);
}
