/* prsg_3.c // Ron Tsur // 07-JUN-95 // */

/* General Purpose LC Pseudo Random Sequence Generator */

#include	"prsg.h"

unsigned char Xor2[4] =		/* 2-input XOR function state table */
{
    /*  --------------------  */
    /*   B   A            X   */
    /*  --------------------  */
    /*   0   0   */       0,
    /*   0   1   */       1,
    /*   1   0   */       1,
    /*   1   1   */       0
    /*  --------------------  */
};


unsigned int
Prsg03 (unsigned int seed)
{
    /* two-input XOR function state table */

    static unsigned long	accumulator;
    int	t;

    if (seed == 0)
    {
	/* reinitialize PRSG */

	accumulator = ORDER_03;
	return accumulator;
    }

    /* create an index value [0..3] for XOR function evaluation */

    t = ((accumulator & Q02) >> 1) |
	((accumulator & Q03) >> 1); 

    if (Xor2[t] == 1)	/* shift left and set MS bit to 1 */
    {
	accumulator = (accumulator << 1) | 1;
    }
    else
    {
	accumulator <<= 1;	/* shift and set MS bit to 0 (implied) */
    }

    accumulator &= ORDER_03;	/* strip irrelevant bits */

    return ((accumulator == ORDER_03) ? 0 : accumulator);
}


main (int argc, char *argv[])
{
    int		i;
    unsigned int val = 0;

    for (i = 0; i <= 7; i++)
    {
	val = Prsg03(val);	
	printf("%d\n", val);
    }
}
