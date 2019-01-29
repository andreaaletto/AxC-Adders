#include "inexact_adders.h"
#include <stdlib.h>
#include <math.h>

static int AMA4_sum(int a, int b, int cin);
static int AMA4_carry(int a, int b, int cin);

int AMA4_adder(int nab, int a, int b )
{
	int i;
       	int current_carry = 0;
	int lsb_a, lsb_b, lsb_sum;
        int acc = 0;
	for(i = 0; i < nab; i++){
		lsb_a = (a & (1U<<i)) >> i;
		lsb_b = (b & (1U<<i)) >> i;
		lsb_sum = AMA4_sum(lsb_a, lsb_b, current_carry);
		acc |= (lsb_sum << i);
		current_carry = AMA4_carry(lsb_a, lsb_b, current_carry);
	}
	int mask = ~((1U << nab) -1);
	int precise_a = a & mask; 
	int precise_b = b & mask;
       	return precise_a + precise_b + acc;	
}

static int AMA4_sum(int a, int b, int cin)
{
	if(	(0 == a && 0 == b && 1 == cin) ||
	   	(0 == a && 1 == b && 1 == cin) ||
		(1 == a && 1 == b && 1 == cin))
		return 1;
	return 0;	
}

static int AMA4_carry(int a, int b, int cin)
{
	return a;
}
