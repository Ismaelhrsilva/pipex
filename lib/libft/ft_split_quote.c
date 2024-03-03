/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_quote.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishenriq <ishenriq@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 19:29:07 by ishenriq          #+#    #+#             */
/*   Updated: 2024/03/03 18:36:01 by ishenriq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_split_quote(char *tmp, char ***splitted)
{
	int		i;
	char	sign;

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
	*splitted = ft_split(tmp, ' ');
	i = 0;
	while (*(*(splitted) + i))
		ft_strrplc(*(*(splitted) + i++), 0x1A, ' ');
	free(tmp);
}
