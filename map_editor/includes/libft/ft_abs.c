#include "libft.h"

long double ft_abs(long double i)
{
    if (i < 0)
        return (-1.0 * i);
    return (i);    
}