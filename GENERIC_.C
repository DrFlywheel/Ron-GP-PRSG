/* ron_prsg.c // Ron Tsur // 18-MAY-95 // */

/*
    General purpose, maximal period, pseudo random sequence generator

    Note:
	This code is a software simulaton of a hardware
	implementation that I did, In another life, around 1975.
	Sequences up to Order 18 have actually been verified.
	Higher order sequences were only partially verified,
	due to the amount of time necessary to traverse through
	all states.

	I slightly modified this implemenation, relative to 
	the original hardware-based realization, by installing
	the ability to produce a state of ZERO.  Consequently, 
	a generator of order N, can produce all (2 ** N) values,
	rather than (2 ** N - 1) values.
*/

#include	"prsg.h"

struct prsg_attr
{
    unsigned long	order_mask,	
			bit_a,
			bit_b,
			bit_c,
			bit_d;

    int			a_shift,
			b_shift,
			c_shift,
			d_shift;
} ;

struct prsg_attr	Attributes[33] =
{
    NA, NA, NA, NA, NA, NA, NA, NA, NA,			/* Order  0 */	
    NA, NA, NA, NA, NA, NA, NA, NA, NA,			/* Order  1 */	
    NA, NA, NA, NA, NA, NA, NA, NA, NA,			/* Order  2 */	

    ORDER_03, Q02, Q03, NA, NA, 1, 1, NA, NA,		/* Order  3 */	
    ORDER_04, Q03, Q04, NA, NA, 2, 2, NA, NA,		/* Order  4 */	
    ORDER_05, Q04, Q05, NA, NA, 3, 3, NA, NA,		/* Order  5 */	
    ORDER_06, Q05, Q06, NA, NA, 4, 4, NA, NA,		/* Order  6 */	
    ORDER_07, Q06, Q07, NA, NA, 5, 5, NA, NA,		/* Order  7 */	
    ORDER_08, Q02, Q03, Q04, Q08, 1, 1, 1, 4,		/* Order  8 */	
    ORDER_09, Q05, Q09, NA, NA, 4, 7, NA, NA,		/* Order  9 */	
    ORDER_10, Q07, Q10, NA, NA, 6, 8, NA, NA,		/* Order 10 */	
    ORDER_11, Q09, Q11, NA, NA, 8, 9, NA, NA,		/* Order 11 */	
    ORDER_12, Q02, Q10, Q11, Q12, 1, 8, 8, 8,		/* Order 12 */	
    ORDER_13, Q01, Q11, Q12, Q13, 0, 9, 9, 9,		/* Order 13 */	
    ORDER_14, Q02, Q12, Q13, Q14, 1, 10, 10, 10,	/* Order 14 */	
    ORDER_15, Q14, Q15, NA, NA, 13, 13, NA, NA,		/* Order 15 */	
    ORDER_16, Q11, Q13, Q14, Q16, 10, 11, 11, 12,	/* Order 16 */	
    ORDER_17, Q14, Q17, NA, NA, 13, 15, NA, NA,		/* Order 17 */	
    ORDER_18, Q11, Q18, NA, NA, 10, 16, NA, NA,		/* Order 18 */	
    ORDER_19, Q14, Q17, Q18, Q19, 13, 15, 15, 15,	/* Order 19 */	
    ORDER_20, Q17, Q20, NA, NA, 16, 18, NA, NA,		/* Order 20 */	

    NA, NA, NA, NA, NA, NA, NA, NA, NA,			/* Order 21 */	
    NA, NA, NA, NA, NA, NA, NA, NA, NA,			/* Order 22 */	
    NA, NA, NA, NA, NA, NA, NA, NA, NA,			/* Order 23 */	
    NA, NA, NA, NA, NA, NA, NA, NA, NA,			/* Order 24 */	
    NA, NA, NA, NA, NA, NA, NA, NA, NA,			/* Order 25 */	
    NA, NA, NA, NA, NA, NA, NA, NA, NA,			/* Order 26 */	
    NA, NA, NA, NA, NA, NA, NA, NA, NA,			/* Order 27 */	
    NA, NA, NA, NA, NA, NA, NA, NA, NA,			/* Order 28 */	
    NA, NA, NA, NA, NA, NA, NA, NA, NA,			/* Order 29 */	
    NA, NA, NA, NA, NA, NA, NA, NA, NA,			/* Order 30 */	

    ORDER_31, Q07, Q31, NA, NA, 6, 29, NA, NA,		/* Order 31 */	

    NA, NA, NA, NA, NA, NA, NA, NA, NA			/* Order 32 */	
};


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
Prsg (int order, unsigned int seed)
{
    static unsigned long	accumulator;
    int	t;

    if ((order > 32) || (order < 0) || (Attributes[order].bit_a == NA))
    {
	/* Cannot handle requested Order */

	return (unsigned int) 0x0;	/* error */
    }

    if (seed == 0)
    {
	/* reinitialize PRSG */

	accumulator = Attributes[order].order_mask;
	return accumulator;
    }

    if (Attributes[order].bit_c == NA)	/* TYPE 2 */
    {
	/* create an index value [0..3] for 2-input XOR function evaluation */

	t = ((accumulator & Attributes[order].bit_a) >> Attributes[order].a_shift) |
	    ((accumulator & Attributes[order].bit_b) >> Attributes[order].b_shift); 

	if (Xor2[t] == 1)	/* shift left and set MS bit to 1 */
	{
	    accumulator = (accumulator << 1) | 1;
	}
	else
	{
	    accumulator <<= 1;	/* shift and set MS bit to 0 (implied) */
	}
    }
    else	/* TYPE 4 */
    {
	/* create an index value [0..15] for 4-input XOR function evaluation */

	t = ((accumulator & Attributes[order].bit_a) >> Attributes[order].a_shift) |
	    ((accumulator & Attributes[order].bit_b) >> Attributes[order].b_shift) |
	    ((accumulator & Attributes[order].bit_c) >> Attributes[order].c_shift) |
	    ((accumulator & Attributes[order].bit_d) >> Attributes[order].d_shift);

	if (Xor4[t] == 1)	/* shift left and set MS bit to 1 */
	{
	    accumulator = (accumulator << 1) | 1;
	}
	else
	{
	    accumulator <<= 1;	/* shift and set MS bit to 0 (implied) */
	}
    }

    accumulator &= Attributes[order].order_mask;   /* strip irrelevant bits */

    return ((accumulator == Attributes[order].order_mask) ? 0x0 : accumulator);
}


/*---------------------*/
/* Test Driver Program */
/*---------------------*/

#include	<stdio.h>

int
main (int argc, char *argv[])
{
    int			i, last, order;
    unsigned int	val = 0;

    order = atoi(argv[1]);
    last = ((1 << order) - 1);

    for (i = 0; i <= last; i ++)
    {
	val = Prsg(order, val);
	printf("%d\n", val);
    }
}
