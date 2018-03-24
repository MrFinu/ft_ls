/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdikilu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/16 00:30:26 by fdikilu           #+#    #+#             */
/*   Updated: 2018/03/24 09:36:12 by fdikilu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void flags_on(unsigned char *tmp, int c)
{	
	if (c == 'l')
		*tmp |= FLAG_L;
	else if (c == 'R')
		*tmp |= FLAG_UPR;
	else if (c == 'a')
		*tmp |= FLAG_A;
	else if (c == 'r')
		*tmp |= FLAG_R;
	else if (c == 't')
		*tmp |= FLAG_T;
	else if (c == '-' && (*tmp == NO_FLAG))
		return ;
	else
	{
		*tmp |= FLAG_ERR;
		*tmp &= FLAG_ERR;
		return ;
	}
}

static void	init_flags(char *s, unsigned char *flags)
{
	unsigned char	tmp;

	++s;
	if (*s == '\0')
	{
		*flags |= FLAG_ERR;
		return ;
	}
	tmp = NO_FLAG;
	while (*s)
	{
		flags_on(&tmp, *s);
		++s;
	}
	*flags |= tmp;
}

static t_ldir	*parse(char *s, DIR *fdir, t_ldir **l_dir)
{
	t_ldir	*new;
	t_ldir	*tmp;

	if (!(*l_dir))
	{
		if (!(*l_dir = (t_ldir *)malloc(sizeof(**l_dir))))
			return (NULL);
		(*l_dir)->name = s;
		(*l_dir)->f_dir = fdir;
		(*l_dir)->next = NULL;
	}
	else
	{
		tmp = *l_dir;
		while (tmp->next)
			tmp = tmp->next;
		if (!(new = (t_ldir *)malloc(sizeof(*new))))
			return (NULL);
		new->name = s;
		new->f_dir = fdir;
		new->next = NULL;
		tmp->next = new;
	}
	return (*l_dir);
}

t_ldir	*ft_parse(char **av, unsigned char *flags)
{
	DIR		*fdir;
	t_ldir	*l_dir;

	++av;
	l_dir = NULL;
	while (*av)
	{
		if (*flags & FLAG_ERR || (**av == '-' && ft_strlen(*av) == 1))
		{
			printf("usage: [-lRart] [file ...]\n");
			return (NULL);
		}
		else if (**av == '-')
			init_flags(*av, flags);
		else if ((fdir = opendir(*av)))
		{
			if (!(l_dir = parse(*av, fdir, &l_dir)))
			{
				if ((closedir(fdir) == -1))
					perror("closedir");
				return (NULL);
			}
			if ((closedir(fdir) == -1))
			{
				perror("closedir");
				return (NULL);	
			}
		}
		else
		{
			printf("not a directory\n");
		}
		++av;
	}
	return (l_dir);
}
