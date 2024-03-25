#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>
#include "baconCode.h"

int main(int argc, char **argv) {
	/*
		Read from stdin, and convert each character to a 5 letter modified "Bacon" code.

		While(not end of file for stdin)
			Read the next character from standard input.
			If there are no more characters, quit the loop.
			If the character is a new-line('\n') copy it to stdout and restart the loop
			Find the index of each (lowercased) character in "alfa" ... if not found, use the index of '*'.
			Treat the index as a five bit binary number
			Loop through the five bits in the binary number, from left to right
				A binary digit of "0" in the index causes a vowel randomly chosen from "vowels" to be written to stdout
				A binary digit of "1" in the index causes a consonant randomly chosen from "consonants" to be written to stdout
				Spaces are injected in stdout randomly between 1 to 8 character chunks
	*/
	srand(time(0)); // Use the current time as the seed for random generator

	// TODO: Your encode code goes here...
	char inp;
	int ind;
	while ((inp = getchar()) != EOF)
	{
		if (inp == '\n')
		{
			printf("\n");
			continue;
		}
		inp = tolower(inp);
		char * foundPtr = strchr(alfa, inp);
		if (foundPtr != NULL)
		{
			ind = foundPtr - alfa;
			//printf("Character %c is found at index %d\n",inp, ind);
		}
		else
		{
			ind = strlen(alfa) - 1;
			//printf("Character %c is found at index %d\n",inp, ind);
		}
		int r = 1;
		int ch = 0;
		for (int i = 4; i >= 0; i--)
  		{
		      	int j = ind >> i;
		      	if (r <= ch)
		      	{
		      		printf(" ");
		      		r = 1 + rand() % 8;
		     	}
      			if (j & 1)
      			{
        			//printf("this is 1\n");
				printf("%c", consonants[rand()%strlen(consonants)]);
				ch++;
      			}
      			else
      			{
      				//printf("this is 0\n");
				printf("%c", vowels[rand()%strlen(vowels)]);
				ch++;
      			}
  		}
	}	
	return 0;
}
