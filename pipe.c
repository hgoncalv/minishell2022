#include "../headers/headers.h"

/* links env with command*/
char		*ft_env_cm(char **env, char *cm)
{
	char	**list_path;
	char	*tmp_path;
	char	*cm_path;

	while (*env)
	{
		if (ft_strnstr(*env, "PATH", 4) != 0)
			break;
		env++;
	}
	list_path = ft_strsplit(*env, ':');
	while (*list_path)
	{
		tmp_path = ft_strjoin(*list_path, "/");
		cm_path = ft_strjoin(tmp_path, cm);
		free(tmp_path);
		if (access(cm_path, F_OK) == 0)
			return (cm_path);
		else
			list_path++;
	}
	return (0);
}

/* execute command by finding command and env link in ft_execute_env_cm */
void		ft_execve(char *ag, char **env)
{
	char	**list_cm;

	list_cm = ft_strsplit(ag, ' ');
	if (execve(ft_env_cm(env, list_cm[0]), list_cm, env) == -1)
	{
		perror("ft_exceve");
		exit(1);
	}
}

/* OPEN document and send output through pipe/parent_p */
void		child_p(int *fd, char **ag, char **env)
{
	int		filefd;
	
	filefd = open(ag[1], O_RDONLY, 0777);
	if (filefd == -1)
	{
		perror("child_p- make sure file exist");
		exit(2);
	}
	dup2(fd[1], 1);
	dup2(filefd, 0);
	close(fd[0]);
	ft_execve(ag[2], env);
}

/* READS from pipe, ST_INPUT is ST_OUT of child_p */
void		parent_p(int *fd, char **ag, char **env)
{
	int		filefd;
	
	// filefd = open("mytesting.txt", O_RDWR | O_CREAT | O_TRUNC,  0777);
	filefd = open(ag[4], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (filefd == -1)
	{
		perror("parent_p");
		exit(2);
	}
	dup2(fd[0], 0);
	dup2(filefd, 1);
	close(fd[1]);
	ft_execve(ag[3], env);
}


/* MAIN function, creates a pipe, forks/creates 2 running procceses same time,
waits for the child to finish, pass output to paretnt, stores output in ag[4] */
int			main(int ac, char **ag, char **env)
{
	int	fd[2];
	int	pid;

	if (ac != 5)
		printf("You have a wrong number of arguments (!5)");
	else
	{
		pipe(fd);
		pid = fork();
		if (pid == 0)
			child_p(fd, ag, env);
		else
		{
			waitpid(pid, NULL, 0);
			parent_p(fd, ag, env);
		}
		close(fd[0]);
		close(fd[1]);
	}
	return (0);
}