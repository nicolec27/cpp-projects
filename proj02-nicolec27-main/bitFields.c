#include "bitFields.h"
#include <assert.h>

int getBit(int bn,unsigned long val) {
	// TODO:
	//		check to make sure bn is a valid bit position in long (you may assert this is true)
	//		If the bit in val at position bn is 1, return 1
	//		otherwise return 0.
	assert((bn >= 0) && (bn < 64));
	
	int result = (val>>bn)&1L;
	if (result == 1)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

void setBit(int bn,int new,unsigned long *val) {
	// TODO:
	//		check to make sure bn is a valid bit position in long (you may assert this is true)
	//		if new is true, set the bit in val at bn to 1
	//     otherwise, set the bit in val at bn to 0
	assert((bn >= 0) && (bn < 64));
	if (new == 1)
	{
		*val |= 1L << bn;
	}
	else
	{
		*val &= ~(1L << bn);
	}
}

long getBitFld(int bs,int len,unsigned long val) {
	// TODO:
	//		check to make sure bs is a valid bit position in long (you may assert this is true)
	//		check to make sure len is a valid length for a subfield that starts at bs (you may assert this is true)
	// 		perform an unsigned getBitFldU to extract the unsigned version of the field
	//		get the high order bit of the result... that's the "sign" bit
	//		if the sign bit not zero, replace the 0 padding with 1 padding
	assert((bs >= 0) && (bs < 64));
  	assert((len >= 1) && (len <= (bs+1)));
	unsigned long result = getBitFldU(bs, len, val);
	int signb = val<<(1L-1);
	if (signb != 0)
	{
		for (int i = len; i < 64; i++)
		{
			setBit(i, 1, &result);
		}
	}
	return result;
}

unsigned long getBitFldU(int bs,int len,unsigned long val) {
	// TODO:
	//		check to make sure bs is a valid bit position in long (you may assert this is true)
	//		check to make sure len is a valid length for a subfield that starts at bs (you may assert this is true)
	// 		make a mask that has len 1's
	// 		Shift that mask left so it's leftmost 1 starts at bs
	//      bitwise and the mask and val to isolate the bit field bits
	//		Shift the result to the right so that the rightmost bit of the bit field is bit 0
	//			Note that shift right pads to the left with the sign bit if the field is signed, but
	//			for unsigned, it will pad to the left with 0
	assert((bs >= 0) && (bs < 64));
  	assert((len >= 1) && (len <= (bs+1)));
	unsigned long mask = (1L<<len)-1;
	mask = mask << (bs-len+1);
	unsigned long result = (mask&val) >> (bs-len+1);
	return result;
}

void setBitFld(int bs,int len,unsigned long new,unsigned long *val) {
	// TODO:
	//		check to make sure bs is a valid bit position in long (you may assert this is true)
	//		check to make sure len is a valid length for a subfield that starts at bs (you may assert this is true)
	//      Make a mask that has len bits, right justified
	//		Use mask to turn off any bits to the left of the bitField values in new
	// 		Shift both the new value and the mask to the correct bit position
	//		Turn off all bits in *val under the mask by bitwise anding with ~mask
	//		Or *val with new.  (new has zeros for all non bit field positions, so won't affect val)
	assert((bs >= 0) && (bs < 64));
  	assert((len >= 1) && (len <= (bs+1)));
	unsigned long mask = (1L<<len)-1;
	//new &= ~(mask >> (bs-len+1));
	new = new&mask;
	new = new << (bs-len+1);
	mask = mask << (bs-len+1);
	*val &= ~(mask); // for &= and |=, https://www.geeksforgeeks.org/operators-c-c/?ref=gcse
	*val |= new;
}
