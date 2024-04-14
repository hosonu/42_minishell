#include "../../includes/minishell.h"

char	*format_path(char *av, char buff[PATH_MAX])
{
	char	*path;
	int	i;

	i = 0;
	if (av == NULL)
		ft_strlcpy(buff, "/", PATH_MAX);
	else if (av[0] == '~')
	{
		path = getenv("HOME");
		while (av[i] != '/' && av[i] != '\0')
			i++;
		ft_strlcpy(buff, path, PATH_MAX);
		ft_strlcat(buff, &av[i], PATH_MAX);
	}
	else
		ft_strlcpy(buff, av, PATH_MAX);
	return buff;
}

void	cd_change_env(t_env *env)
{
	t_env	*pwd;
	t_env	*old;
	char	pwd_buff[PATH_MAX];

	if (getcwd(pwd_buff, PATH_MAX) == NULL)
		perror("cd");
	old = getenv_node(env, "OLDPWD");
	pwd = getenv_node(env, "PWD");
	free(old->value);
	old->value = ft_strdup(pwd->value);
	free(pwd->value);
	pwd->value = ft_strdup(pwd_buff);
}

int	ft_cd(char *av[], t_env *env)
{
	t_env	*pwd;
	t_env	*old;
	char	format_buff[PATH_MAX];
	int	i;

	i = 0;
	format_path(av[0], format_buff);
	if (chdir(format_buff) == -1)
	{
		printf("No such file or directory\n");
		return (1);
	}
	else
		cd_change_env(env);
	return (0);
}
