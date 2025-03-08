static int	check_access(char **filepath, char **resolved_path)
{
	if (access(*filepath, F_OK) == 0)
	{
		if (access(*filepath, X_OK) == 0)
		{
			if (*resolved_path != NULL)
			{
				free(*resolved_path);
			}
			*resolved_path = *filepath;
			return (0);
		}
		if (*resolved_path == NULL)
		{
			*resolved_path = *filepath;
			*filepath = NULL;
		}
	}
	if (*filepath != NULL)
	{
		free(*filepath);
		filepath = NULL;
	}
	return (-1);
}

static int	get_pathname(t_child *child, char **argv, char **pathname)
{
	char	*temp;
	size_t	idx;

	idx = 0;
	*pathname = NULL;
	while (child->path[idx])
	{
		temp = pathjoin(child->path[idx++], argv[0]);
		if (temp == NULL)
		{
			terminate("malloc failed", -1);
			if (pathname != NULL)
				free(pathname);
			return (-1);
		}
		if (check_access(&temp, &pathname) != -1)
		{
			return (0);
		}
	}
	return (0);
}
