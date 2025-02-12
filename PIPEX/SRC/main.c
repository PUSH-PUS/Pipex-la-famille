/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkiefer <nkiefer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 13:45:06 by nkiefer           #+#    #+#             */
/*   Updated: 2025/01/31 15:49:34 by nkiefer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	error_exit(const char *message, char **to_free)
{
	if (to_free)
		ft_free_split(to_free);
	perror(message);
	exit(EXIT_FAILURE);
}

void	error_msg(char **cmd_args, char *msg, int code)
{
	ft_putstr_fd("pipex: ", STDERR_FILENO);
	ft_putstr_fd(*cmd_args, STDERR_FILENO);
	if (msg && *msg)
		ft_putstr_fd(msg, STDERR_FILENO);
	write(STDERR_FILENO, "\n", 1);
	ft_free_split(cmd_args);
	exit(code);
}

void	close_pipes(t_pipex *pipex)
{
	close(pipex->pipefd[0]);
	close(pipex->pipefd[1]);
}

void	init_pipex(t_pipex *pipex, char **envlp, char *outfile_name)
{
	pipex->envlp = envlp;
	pipex->outfile_name = outfile_name;
}

int	main(int argc, char **argv, char **envlp)
{
	t_pipex	pipex;

	if (argc != 5)
	{
		ft_putstr_fd("Usage: ./pipex infile cmd1 cmd2 outfile\n", 2);
		exit(EXIT_FAILURE);
	}
	init_pipex(&pipex, envlp, argv[4]);
	run_pipex(&pipex, argv);
	return (EXIT_SUCCESS);
}
