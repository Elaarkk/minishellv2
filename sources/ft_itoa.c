/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguilleu <aguilleu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 20:00:32 by acolonne          #+#    #+#             */
/*   Updated: 2025/05/20 15:23:58 by aguilleu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	len_nb(long nbr)
{
	int	len;

	len = 0;
	if (nbr < 0)
		nbr = -nbr;
	while (nbr)
	{
		nbr = nbr / 10;
		len++;
	}
	return (len);
}

static char	*zero(void)
{
	char	*nb;

	nb = malloc(2);
	if (!nb)
		return (0);
	nb[0] = '0';
	nb[1] = '\0';
	return (nb);
}

static char	*put_in_numbers(long nbr, int signe)
{
	char	*nb;
	int		len;
	int		end;

	len = len_nb(nbr);
	end = len;
	nb = malloc(len + signe + 1);
	if (!nb)
		return (0);
	if (signe == 1)
	{
		nb[0] = '-';
		nbr = -nbr;
	}
	len--;
	while (nbr > 0)
	{
		nb[signe + len] = (nbr % 10) + 48;
		nbr = nbr / 10;
		len--;
	}
	nb[end + signe] = '\0';
	return (nb);
}

char	*ft_itoa(int n)
{
	char	*nb;
	long	nbr;
	int		signe;

	nbr = n;
	signe = 0;
	if (nbr == 0)
		return (zero());
	if (n < 0)
		signe = 1;
	nb = put_in_numbers(nbr, signe);
	return (nb);
}
