#include "window.h"

bool	member_of_set(char c, char *set)
{
	if (!set)
		return (false);
    while (*set) 
	{
        if (*set == c) 
            return true;
        set++;
    }
    return false;
}

int	array_len(char **arr)
{
	int	i;
	
	i = 0;
	while (arr[i])
	{
		i++;
	}
	return (i);
}

