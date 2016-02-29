/* GPprsg.h // Ron Tsur // 07-JUN-95 // */

/******************************************************************************

    General purpose, maximal period, pseudo random sequence generator
	Copyright (C) Ron Tsur 1995 through 2005.

  Notices:
	This code is a software simulaton of a hardware LFSR
	implementation that I did, In another life, around 1975.
	Sequences up to Order 28 have been fully verified for state
	correctness. Higher order sequences were only partially verified,
	due to the large amount of time necessary to traverse through all states.

	I slightly modified this implemenation, relative to 
	the original hardware-based realization, by installing
	the ability to produce a state of ZERO.  Consequently, 
	a generator of order N, can produce all (2 ** N) values,
	rather than (2 ** N - 1) values.

	
	Open Source and Free Software Release:
	--------------------------------------

	Use this software at your own risk. The author believes this code to perform
	correctly and makes no specific claims or warranties regading the behavior of
	this software.

	Permission to use this code, without monetary remuneration to the author,
	in either source or executable form and without requiring a specific license,
	is hereby granted to all parties, provided that proper credit to the Author,
	is incorporated, in additon to this unmodified notice, into the released
	program code, and the release notes, accompanying the software distribution
	of the final product. The term final product also pertains to code libraries,
	whether in source or linkable form. 
	
	All of the above conditions pertain to all segments of the code,
	as well as to modified versions of any part(s) of this source code.

******************************************************************************/

#define	NA		0		/* "Not Applicable" mark */

#define	ORDER_03		0x00000007
#define	ORDER_04		0x0000000f
#define	ORDER_05		0x0000001f
#define	ORDER_06		0x0000003f
#define	ORDER_07		0x0000007f
#define	ORDER_08		0x000000ff
#define	ORDER_09		0x000001ff
#define	ORDER_10		0x000003ff
#define	ORDER_11		0x000007ff
#define	ORDER_12		0x00000fff
#define	ORDER_13		0x00001fff
#define	ORDER_14		0x00003fff
#define	ORDER_15		0x00007fff
#define	ORDER_16		0x0000ffff
#define	ORDER_17		0x0001ffff
#define	ORDER_18		0x0003ffff
#define	ORDER_19		0x0007ffff
#define	ORDER_20		0x000fffff
#define	ORDER_21		0x001fffff
#define	ORDER_22		0x003fffff
#define	ORDER_23		0x007fffff
#define	ORDER_24		0x00ffffff
#define	ORDER_25		0x01ffffff
#define	ORDER_26		0x03ffffff
#define	ORDER_27		0x07ffffff
#define	ORDER_28		0x0fffffff
#define	ORDER_29		01ffffffff
#define	ORDER_30		0x3fffffff
#define	ORDER_31		0x7fffffff
#define	ORDER_32		0xffffffff

#define	Q01		(1 << 0)
#define	Q02		(1 << 1)
#define	Q03		(1 << 2)
#define	Q04		(1 << 3)
#define	Q05		(1 << 4)
#define	Q06		(1 << 5)
#define	Q07		(1 << 6)
#define	Q08		(1 << 7)
#define	Q09		(1 << 8)
#define	Q10		(1 << 9)
#define	Q11		(1 << 10)
#define	Q12		(1 << 11)
#define	Q13		(1 << 12)
#define	Q14		(1 << 13)
#define	Q15		(1 << 14)
#define	Q16		(1 << 15)
#define	Q17		(1 << 16)
#define	Q18		(1 << 17)
#define	Q19		(1 << 18)
#define	Q20		(1 << 19)
#define	Q21		(1 << 20)
#define	Q22		(1 << 21)
#define	Q23		(1 << 22)
#define	Q24		(1 << 23)
#define	Q25		(1 << 24)
#define	Q26		(1 << 25)
#define	Q27		(1 << 26)
#define	Q28		(1 << 27)
#define	Q29		(1 << 28)
#define	Q30		(1 << 29)
#define	Q31		(1 << 30)
#define	Q32		(1 << 31)
