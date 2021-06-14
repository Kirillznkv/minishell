#include "../includes/minishell.h"

int		main(int argc, char **argv, char **env)
{
	char		*line;
	t_commands	cmd;
	int i = 1;	

	cmd.argc = argc;
	cmd.argv = (char **)malloc(sizeof(char *) * argc);
	cmd.argv[argc - 1] = NULL;
	while (argv[i])
	{
		cmd.argv[i - 1] = ft_strdup(argv[i]);
		i++;
	}
	//parse_command(&cmd, env);
	free_char_array(cmd.argv);
	while (1)
		;
	return (0);
}