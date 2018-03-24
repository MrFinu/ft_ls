/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdikilu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/16 02:34:30 by fdikilu           #+#    #+#             */
/*   Updated: 2018/03/24 09:37:42 by fdikilu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		main(int ac, char **av)
{
	t_ldir			*l_dir;
	unsigned char	flags;

	(void)av;
	if (ac < 1)
		return (0);
	if (!(l_dir = ft_parse(av, &flags)))
	{
		printf("\t\t\tListe non creer\n");
		return (0);
	}
	ft_putstr("flags :");
	ft_putnbr((int)flags);
	ft_putchar('\n');
	while (l_dir)
	{
		printf("%s\n", l_dir->name);
		l_dir = l_dir->next;
	}
	return (0);
}
