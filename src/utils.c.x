
#include "pipex.h"

char	**get_path(char **envp)
{
	while (*envp)
	{
		if (!ft_strncmp(*envp, "PATH=", 5))
			return (ft_split(*envp + 5, ':')); //? NULL
		envp++;
	}
	return (NULL);
}
