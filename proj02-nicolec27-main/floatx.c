#include "floatx.h"
#include "bitFields.h" // Remove this if you don't use bitFields
#include <assert.h>
#include <limits.h> // for CHAR_BIT - number of bits per byte
#include <math.h> // for isinf and isnan

floatx doubleToFloatx(double val,int totBits,int expBits) {

/*-----------------------------------------------------------------------------------------------
	From the README: 	At a high level, doing the conversion requires several manipulations:
	1. Extracting the sign bit from the double value, and inserting it into the floatx value at
		the correct position.
	2. Handle special cases, such as 0.0, infinity, or not-a-number.
	3. Extract the biased exponent from the double value.
			Check to see if the double value is sub-normal. If so, handle it.
			Check to make sure the floatx exponent won't overflow or underflow).
					If so, handle as a special case.
			If not, rebias the exponent using the floatx bias (which depends on the number of exponent bits)
			and write the result to the correct location in the floatx result.
	4. Extract the fraction bits from the double value.
			Determine how many bits are available for the fraction in the floatx value,
			and truncate or extend the original value,
			and write the resulting bits to the floatx result.
	6. Return the floatx result.
----------------------------------------------------------------------------------------------------*/

	// First, make some assertions to ensure the totBits and expBits parameters are OK
	// Then, implement the algorithm
	assert(totBits < 64);
	assert(expBits < totBits);
	union hexDouble {
   		double dbl;
   		long lng;
	} unionVal;
	unionVal.dbl = val; // copy val into unionVal.dbl
	int sb = getBit(63, unionVal.lng); // use getBit() to extract the sign bit at 63
	floatx result = 0; // initialize floatx variable
	setBit(totBits-1, sb, &result); // set the correct bit in floatx to the sign bit extracted
	if (unionVal.dbl == 0.0)
	{
		return result;
	}
	if (isinf(unionVal.dbl))
	{
		unsigned long mask = (1L<<expBits)-1; //(1L<<n)-1
		setBitFld(totBits-2,expBits,mask,&result);
		return result;
	}
	if (isnan(unionVal.dbl))
	{
		return result;
	}
	unsigned long exp = getBitFldU(62,11,unionVal.lng); // Extract the biased exponent from the double value. exponent of a double value is 11 bits and begins at bit length 62 (after sign bit)
	exp = exp - 1023; // unbias
	exp = exp + pow(2,(expBits-1))-1; //2**(expBits-1) - 1 add implicit 1 (trunucate?)
	if (exp < 0) //underflow
	{
		return 0;
	}
	if (exp > (((1L<<expBits)-1))) //overflow
	{ 
		unsigned long amask = (1L<<expBits)-1;
		setBitFld(totBits-2,expBits,amask,&result);
		return result;
	}
	setBitFld((totBits-2),expBits,exp,&result); 
	unsigned long frac = getBitFldU(51,(totBits-1-expBits),unionVal.lng); //Extract the fraction bits from the double value
	setBitFld((totBits-2-expBits),(totBits-1-expBits),frac,&result); //16-1-4 --> totBits-sb-expBits
	return result;
}
