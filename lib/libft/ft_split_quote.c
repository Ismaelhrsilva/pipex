/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_quote.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishenriq <ishenriq@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 19:29:07 by ishenriq          #+#    #+#             */
/*   Updated: 2024/03/07 02:42:57 by ishenriq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_split_quote(char *tmp)
{
	int		i;
	int		j;
	char	sign;
	char	**splitted;

	i = -1;
	sign = 0;
	while (tmp && *(tmp + ++i))
	{
		if (sign && *(tmp + i) == sign)
		{
			*(tmp + i) = ' ';
			sign = 0;
		}
		else if (!sign && (*(tmp + i) == '\"' || *(tmp + i) == '\''))
		{
			sign = *(tmp + i);
			*(tmp + i) = ' ';
		}
		else if (sign && *(tmp + i) == ' ')
			*(tmp + i) = 0x1A;
	}
	splitted = ft_split(tmp, ' ');
	i = 0;
	j = 0;
	while (splitted[j])
		ft_strrplc(splitted[j++], 0x1A, ' ');
	return (splitted);
}
