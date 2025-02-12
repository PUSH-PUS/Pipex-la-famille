/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkiefer <nkiefer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 13:45:29 by nkiefer           #+#    #+#             */
/*   Updated: 2025/01/31 16:21:05 by nkiefer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	handle_input(t_exec *exec, char *filename)
{
	exec->infile_fd = open(filename, O_RDONLY);
	if (exec->infile_fd == -1)
	{
		ft_putstr_fd("pipex: ", STDERR_FILENO);
		perror(filename);
		exec->infile_fd = open("/dev/null", O_RDONLY);
		if (exec->infile_fd == -1)
			error_exit("Error: /dev/null", NULL);
	}
}

static void	clean_exit(char **cmd_args, char *cmd, char *msg, int code)
{
	if (msg)
		error_msg(cmd_args, msg, code);
	else
		error_exit(cmd, cmd_args);
	ft_free_split(cmd_args);
	exit(code);
}

void	handle_absolute_path(char **cmd_args, char **envp)
{
	if (access(cmd_args[0], F_OK) == -1)
		clean_exit(cmd_args, cmd_args[0], "No such file or directory", 127);
	if (access(cmd_args[0], X_OK) == -1)
		clean_exit(cmd_args, cmd_args[0], "Permission denied", 126);
	execve(cmd_args[0], cmd_args, envp);
	clean_exit(cmd_args, cmd_args[0], "execve failed", 1);
}

void	execute_command(char *cmd, char **envp)
{
	char	**cmd_args;
	char	*path;

	cmd_args = NULL;
	path = NULL;
	if (ft_strlen(cmd) == 0)
		clean_exit(NULL, "", "command not found", 127);
	cmd_args = split_command(cmd);
	if (!cmd_args || !cmd_args[0])
		clean_exit(cmd_args, "", "command not found", 127);
	if (ft_strchr(cmd_args[0], '/'))
		handle_absolute_path(cmd_args, envp);
	path = find_command_path(cmd_args[0], envp);
	if (!path)
		clean_exit(cmd_args, cmd_args[0], "command not found", 127);
	execve(path, cmd_args, envp);
	free(path);
	clean_exit(cmd_args, cmd_args[0], "execve failed", EXIT_FAILURE);
}

void	run_pipex(t_pipex *pipex, char **argv)
{
	t_exec	exec;
	int		status;

	ft_memset(&exec, 0, sizeof(t_exec));
	handle_input(&exec, argv[1]);
	if (pipe(pipex->pipefd) == -1)
		error_exit("Pipe error", NULL);
	exec.pid1 = fork();
	if (exec.pid1 == 0)
		first_child(pipex, &exec, argv[2]);
	close(pipex->pipefd[1]);
	exec.pid2 = fork();
	if (exec.pid2 == 0)
		second_child(pipex, &exec, argv[3]);
	close(pipex->pipefd[0]);
	close(exec.infile_fd);
	waitpid(exec.pid1, NULL, 0);
	waitpid(exec.pid2, &status, 0);
	if (WIFEXITED(status))
		exit(WEXITSTATUS(status));
	exit(EXIT_FAILURE);
}
