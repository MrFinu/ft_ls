/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdikilu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/16 02:34:30 by fdikilu           #+#    #+#             */
/*   Updated: 2018/10/28 18:22:06 by fdikilu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		main(int ac, char **av)
{
	t_list			*tmp;
	t_ldir			*l_dir;
	unsigned char	flags;

	flags = NO_FLAG;
	if (!(l_dir = ft_parse(ac, av, &flags)))
		return (0);
	while (l_dir)
	{
		if (!(tmp = ft_readdir(l_dir->f_dir, l_dir->name)))
			return (0);
		if (ac != 1)
			printf("%s:\n", l_dir->name);
		while (tmp)
		{
			printf("%s\n", ((t_info *)tmp->content)->name);
			tmp = tmp->next;
		}
		l_dir = l_dir->next;
		free((void *)tmp);
	}
	return (0);
}
