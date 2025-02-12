/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child-binS.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkiefer <nkiefer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 16:24:25 by nkiefer           #+#    #+#             */
/*   Updated: 2025/02/02 14:37:03 by nkiefer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	child_process(t_pipex *pipex, t_exec *exec, t_child *child_data)
{
	if (dup2(child_data->input_fd, STDIN_FILENO) == -1)
		error_exit("Dup2 input", NULL);
	if (dup2(child_data->output_fd, STDOUT_FILENO) == -1)
		error_exit("Dup2 output", NULL);
	close_pipes(pipex);
	close(exec->infile_fd);
	if (exec->outfile_fd > 0)
		close(exec->outfile_fd);
	execute_command(child_data->cmd, pipex->envlp);
}

void	first_child(t_pipex *pipex, t_exec *exec, char *cmd)
{
	close(pipex->pipefd[0]);
	if (dup2(exec->infile_fd, STDIN_FILENO) == -1)
		error_exit("Error: Dup2 failed (input)", NULL);
	close(exec->infile_fd);
	if (dup2(pipex->pipefd[1], STDOUT_FILENO) == -1)
		error_exit("Error: Dup2 failed (output)", NULL);
	close(pipex->pipefd[1]);
	execute_command(cmd, pipex->envlp);
	close(pipex->pipefd[0]);
	close(pipex->pipefd[1]);
}

void	second_child(t_pipex *pipex, t_exec *exec, char *cmd)
{
	t_child	child_data;

	exec->outfile_fd = open(pipex->outfile_name, O_WRONLY | O_CREAT | O_TRUNC,
			0644);
	if (exec->outfile_fd == -1)
		error_exit("Error: Outfile", NULL);
	child_data.input_fd = pipex->pipefd[0];
	child_data.output_fd = exec->outfile_fd;
	child_data.cmd = cmd;
	child_process(pipex, exec, &child_data);
	close(exec->outfile_fd);
	close(pipex->pipefd[0]);
	close(pipex->pipefd[1]);
}

void	initialize_positions_forsplitdemesc(int pos[3])
{
	pos[0] = 0;
	pos[1] = 0;
	pos[2] = 0;
}
