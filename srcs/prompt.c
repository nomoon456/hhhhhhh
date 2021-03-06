/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elbouju <elbouju@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/16 19:39:25 by paulohl           #+#    #+#             */
/*   Updated: 2021/01/27 12:28:39 by elbouju          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "minishell.h"
#include "libft.h"

int g_sig = 0;

int	print_prompt(char *buf)
{
	int		n;

	write(1, "$> ", 3);
	n = read(0, buf, MAX_CMD_LEN);
	buf[n - 1] = 0;
	if (n == MAX_CMD_LEN)
		return (0);
	return (n);
}

int	exit_return(char *buf, t_command *command)
{
	int		exit_value;
	t_env	*tmp;

	exit_value = command->return_value;
	free(buf);
	reset_fds(command);
	while (command->env)
	{
		tmp = command->env->next;
		free(command->env->name);
		free(command->env->value);
		free(command->env);
		command->env = tmp;
	}
	free(command->env);
	free(command);
	return (exit_value);
}

int	start(int argc, char **argv, char **envp)
{
	char		*buf;
	int			err;
	t_command	*command;

	argc = 0;
	argv = NULL;
	if (!(buf = (char *)malloc(sizeof(*buf) * MAX_CMD_LEN)))
		return (GLOB_ERR_MALLOC);
	if (!init_struct(envp, &command))
		return (GLOB_ERR_MALLOC);
	while (1)
	{
		if (!print_prompt(buf))
			return (GLOB_CMD_LEN);
		if (basic_syntax_check(buf, &err))
			print_syntax_error(err);
		else if ((err = parser(buf, command)) == 1)
			return (exit_return(buf, command));
		else if (err)
			print_parser_error(err, command);
	}
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	signal(SIGINT, sigint_handler);
	return (start(argc, argv, envp));
	start(argc, argv, envp);
	system("leaks minishell");
}
