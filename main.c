/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vshchuki <vshchuki@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 23:41:30 by vshchuki          #+#    #+#             */
/*   Updated: 2024/01/04 20:00:24 by vshchuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// https://www.thegeekstuff.com/2010/10/linux-error-codes/
/**
 * In macOS, executables can be stored in various directories, and the location of these directories is specified in the system's PATH environment variable. Common directories for storing executables in macOS include:

/bin: Core system binaries essential for system boot and repair.
/usr/bin: User command binaries.
/usr/local/bin: User-installed binaries (this directory is not part of the system default PATH, but it's commonly used for user-installed software).
/sbin: System binaries for system administration.
/usr/sbin: System binaries for system administration, not intended for normal user use.
/usr/local/sbin: User-installed system administration binaries (similar to /usr/local/bin, not part of the system default PATH).


https://www.geeksforgeeks.org/fork-system-call/
https://www.geeksforgeeks.org/pipe-system-call/

*/
#include "ft_pipex.h"

int get_file_size(char *file_name)
{
	int fd;
	char buffer[1];
	int result;
	int read_bytes;

	fd = open(file_name, O_RDONLY);
	result = 0;
	while (1)
	{
		read_bytes = read(fd, buffer, 1);
		if (read_bytes == 0)
			return (result);
		else if (read_bytes < 0)
		{
			ft_printf("%s\n", strerror(2));
			return (-1);
		}
		result += read_bytes;
	}
	close(fd);
}

char *read_file(char *file_name)
{
	int fd;
	int file_size;
	char *read_file;
	int read_bytes;

	fd = open(file_name, O_RDONLY);
	file_size = get_file_size(file_name);
	read_file = (char *)malloc(file_size);
	read_bytes = read(fd, read_file, file_size);
	close(fd);
	return (read_file);
}

void free_paths(char **paths)
{
	int j;

	j = ft_strlen((char *)paths);
	while (j >= 0)
	{
		free(paths[j]);
		j--;
	}
	free(paths);
}

char **find_paths(char *envp[])
{
	char *line;
	char **paths;

	int i = 0;
	while (envp[i] != NULL)
	{
		// ft_printf("%s\n", envp[i]);
		line = ft_strnstr(envp[i], "PATH=", ft_strlen(envp[i]));
		if (line)
		{
			// ft_printf("%p\n", line);
			// ft_printf("Found!\n");
			// ft_printf("%s\n", envp[i]);
			paths = ft_split(line + 5, ':');
			return (paths);
		}
		i++;
	}
	return (NULL);
}

char *find_exec_path(char **paths, char *name)
{
	char *executable;
	char *temp;

	executable = NULL;
	if (!name || !name[0])
		return (executable);
	while (*paths)
	{
		executable = ft_strdup(*paths);
		temp = executable;
		executable = ft_strjoin(temp, "/");
		free(temp);
		temp = executable;
		executable = ft_strjoin(temp, name);
		free(temp);
		// ft_printf("%s\n", executable);
		if (access(executable, X_OK) == 0)
		{
			// ft_printf("%s\n", *paths);
			// ft_printf("%s\n", executable);
			return (executable);
		}
		paths += 1;
		free(executable);
	}
	return (executable);
}

//	argv[1]		argv[2]		argv[3]		argv[4]
//	file1		cmd1		cmd2		file2

int main(int argc, char *argv[], char *envp[])
{
	// char *file;
	int		fd;
	char	*executable;
	char	**paths;
 	int pipe_fd[2];
	pid_t pid;
	char	*exec_args[3];

	/* 	char *temp;
		char *cmd1;
		int len; */

	/* file = read_file(argv[1]); */
	paths = find_paths(envp);
	
	if (argc == 4)
	{
		if (pipe(pipe_fd) == -1)
		{
			perror("pipe");
			exit(EXIT_FAILURE);
		}

		fd = open(argv[1], O_RDONLY);
		// dup2(fd, pipe_fd[0]);
		// dup2(fd, STDIN_FILENO);
		pid = fork();

		if (pid == 0)
		{
			dup2(fd, STDIN_FILENO);
			dup2(pipe_fd[1], STDOUT_FILENO);
			close(pipe_fd[1]);
			close(pipe_fd[0]);

			// ft_printf("%s\n", file);

			// ft_printf("%s\n", find_path_env_var(envp) + 5);

			executable = find_exec_path(paths, argv[2]);
			// ft_printf("%s\n", executable);
			exec_args[0] = executable;
			exec_args[1] = NULL;
			exec_args[2] = NULL;

			if (execve(executable, exec_args, NULL) == -1)
			{
				free_paths(paths);
				free(executable);
				perror("execve");
				exit(EXIT_FAILURE);
			}
		}
		else
		{
			close(pipe_fd[1]);
			dup2(pipe_fd[0], STDIN_FILENO);
			close(pipe_fd[0]);
			executable = find_exec_path(paths, argv[3]);
			// ft_printf("%s\n", executable);
			free_paths(paths);
			exec_args[0] = executable;
			// exec_args[1] = "-w";
			exec_args[1] = NULL;
			exec_args[2] = NULL;
			// char *const exec_args[] = {executable, "-l", NULL};
			if (execve(executable, exec_args, NULL) == -1)
			{
				free_paths(paths);
				free(executable);
				perror("execve");
				exit(EXIT_FAILURE);
			}  
		}
		// executable = ft_strdup("/bin/bash");

		// temp = executable;
		// len = strlen(argv[2]);
		// cmd1 = ft_substr(argv[2], 0, len);
		// executable = ft_strjoin(temp, cmd1);
		// free(temp);

		/* 	char *exec_args[] = { executable, "-c", argv[1], NULL };
			execve(executable, exec_args, NULL); */

		// if (fd < 0)
		// {
		// 	// perror("");
		// 	ft_printf("%s", strerror(2));
		// 	return (2);
		// }
		// ft_printf("%d", fd);
		free_paths(paths);
		free(executable);
	}
	return (0);
}
