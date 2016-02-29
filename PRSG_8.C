/* prsg_8.c // Ron Tsur // 07-JUN-95 // */

/* General Purpose LC Pseudo Random Sequence Generator */

#include	"prsg.h"

unsigned char Xor4[16] =		/* 4-input XOR function state table */
{
    /* --------------------------- */
    /*   D   C   B   A          X  */
    /* --------------------------- */
    /*   0   0   0   0   */	0,
    /*   0   0   0   1   */	1,
    /*   0   0   1   0   */	1,
    /*   0   0   1   1   */	0,
    /*   0   1   0   0   */	1,
    /*   0   1   0   1   */	0,
    /*   0   1   1   0   */	0,
    /*   0   1   1   1   */	1,
    /*   1   0   0   0   */	1,
    /*   1   0   0   1   */	0,
    /*   1   0   1   0   */	0,
    /*   1   0   1   1   */	1,
    /*   1   1   0   0   */	0,
    /*   1   1   0   1   */	1,
    /*   1   1   1   0   */	1,
    /*   1   1   1   1   */	0
    /* --------------------------- */
};


unsigned int
Prsg08 (unsigned int seed)
{
    /* two-input XOR function state table */

    static unsigned long	accumulator;
    int	t;

    if (seed == 0)
    {
	/* reinitialize PRSG */

	accumulator = ORDER_08;
	return accumulator;
    }

    /* create an index value [0..15] for XOR function evaluation */

    t = ((accumulator & Q02) >> 1) |	/* A */
	((accumulator & Q03) >> 1) |	/* B */
	((accumulator & Q04) >> 1) |	/* C */
	((accumulator & Q08) >> 4) ;	/* D */

    if (Xor4[t] == 1)	/* shift left and set MS bit to 1 */
    {
	accumulator = (accumulator << 1) | 1;
    }
    else
    {
	accumulator <<= 1;	/* shift and set MS bit to 0 (implied) */
    }

    accumulator &= ORDER_08;	/* strip irrelevant bits */

    return ((accumulator == ORDER_08) ? 0 : accumulator);
}


main (int argc, char *argv[])
{
    int		i;
    unsigned int val = 0;

    for (i = 0; i <= 255; i++)
    {
	val = Prsg08(val);	
	printf("%d\n", val);
    }
}
