
// t_cmd	*create_cmd(t_prompt *prompt, t_minishell *minishell)
// {
// 	t_cmd	*cmd;
// 	t_cmd	*tmp;
// 	int		i;
// 	int		j;

// 	i = 0;
// 	j = 0;
// 	cmd = create_cmd_node();
// 	if (!cmd)
// 		return (0);
// 	tmp = cmd;
// 	while (prompt)
// 	{
// 		if (i != 0)
// 		{
// 			tmp = create_cmd_node();
// 			if (!tmp)
// 			{
// 				free_all_cmd(&cmd);
// 				return (0);
// 			}
// 		}
// 		add_cmd(prompt, &tmp, &i, minishell);
// 		while (prompt && (j < i))
// 		{
// 			prompt = prompt->next;
// 			j++;
// 		}
// 		if (cmd != tmp)
// 			ft_cmdadd_back(&cmd, tmp);
// 		if (prompt && prompt->token == PIPE)
// 			prompt = prompt->next;
// 	}
// 	return (cmd);
// }