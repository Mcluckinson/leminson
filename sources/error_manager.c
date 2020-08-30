//
// Created by Carleton Lothor on 8/30/20.
//

#include "lemin.h"

void check_ants_quantity(int quantity)
{
    if (quantity <= 0)
    {
        ft_error("Please get at least one ant.");
    }
    if (quantity >= ANTS_LIMITS)
    {
        char *limits = ft_itoa(ANTS_LIMITS);
        char *error = ft_strjoin("The number of ants is limited, please start them no more than ", limits);
        ft_error(error);
    }
}
