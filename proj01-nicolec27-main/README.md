# proj01 - Encoding and Decoding Text

## Introduction

This project gives some experience in the concrete implementation of integers in the C language, as well as some experience in bit-twiddling in C.

You will need to write the code for two programs, an encoding program and a decoding program. Both of these programs should behave as UNIX "filters"; they should read character input from standard input (stdin), and write character output to standard output (stdout). Any messages designed for human consumption should be written to standard error (stderr). That allows us to use UNIX standard input and output redirection, and we can create invocations such as:

```
>./encode <raw.txt >encoded.txt # Read input from raw.txt and write encoded output to encoded.txt
>./decode <encoded.txt # Read input from encoded.txt and write results to the screen
>/.encode <raw.txt | ./decode # Read input from raw.txt, encode it, decode it, and write results to the screen
```

(See [Introduction to Linux: I/O Redirection](https://tldp.org/LDP/intro-linux/html/sect_05_01.html) if you don't understand redirection.)

We will be using an encoding and decoding mechanism derived from [Bacon's Cipher](https://en.wikipedia.org/wiki/Bacon%27s_cipher), a cipher first documented by Frances Bacon in 1605. Some early conspiracy theorists proposed that Bacon actually wrote the works of Shakespeare, and included hints about the true authorship in Baconian cipher in the Shakespeare first folio printing. That theory has been virtually disproved by, among others, [Elizebeth Smith Friedman](https://en.wikipedia.org/wiki/Elizebeth_Smith_Friedman), who, with her husband, was one of the most important developers of the modern science of cryptology.

![Shakespeare Folio](https://github.com/BinghamtonUniversityCS140/images/blob/master/Shakespeare_Bacon.jpg)

The Bacon Cipher uses the index of each letter in a short alphabet of possible raw text letters, and converts that index into a five bit binary number between 0b00000 = 0 and 0b11111 = 31. Then, each bit of the five digit binary number is used to choose a letter in the encoded text. For example, suppose a 0 bit chooses an 'a' character, and a 1 bit chooses a 'b' character. Then, the letter "d", which is the fourth letter in the alphabet, "abcd...", but has index 3 will result in the five bit number 0b00011, which will produce the encoded text "aaabb". Thus, every input character produces an encoded output that contains five characters.

For our implementation, we will introduce a couple of extra features to create a "modified" Bacon cipher to make the encoded text less obvious. First, we will use a zero bit to choose any random vowel instead of just an "a", and a 1 bit will choose any random consonant instead of just a "b". Secondly, instead of creating groups of five characters in the output, we will join output letters and inject spaces randomly between every 1 to 8 output characters. This means that I can encode the same input text twice and produce very different encoded output, but those different outputs will be decoded back to the same result.

We will use a very simple alphabet. Since we can only represent 32 letters in a 5 bit binary number, we will ignore upper vs. lower case and use only the 26 lower case letters, a-z, plus some punctiation (comma and period), a blank space, and an asterisk (*) to represent any character that is not in the alphabet. (That only uses 30 of the 32 characters we can choose, but it's good enough.)

Finally, by convention, we will leave all newline characters (\n) untranslated so that our encoded text has the same line structure as the raw text.

## Provided to you

The proj01 repository already contains some infrastructure to get you started, as follows:

- **baconCode.h** An include file that contains some basic constants to use in encoding and decoding; `alfa`, `vowels`, and `consonants`. The `alfa` string contains the list of characters in the raw text alphabet in the order to be used. The `vowels` string contains a list of all possible vowels to be used in the encoded text, and the `consonants` string contains all possible consonants to be used in the encoded text.

  If your program includes `baconCode.h`, but does not reference all three variables, you will get a warning message from the compiler about a variable that is defined but not used. The baconCode.h includes a pre-processor macro called `UNUSED` which indicates that you have intentionally not used the variable, and should not get the warning message. For example, if you don't use the `consonants` variable, just add `UNUSED(consonants);` in your main function. Then, you will no longer get the compiler warning: `consonants is defined but not used`.
  
  See the Wikipedia [#include guard](https://en.wikipedia.org/wiki/Include_guard) article for more info about the #ifdef/#define/#endif lines in `baconCode.h`.
  
  Please do not edit the contents of baconCode.h. If you do, you will probably lose points for the project.
  
- **baconEncode.c** - The start of the program to encode raw text into ciphered text. You will need to edit this file to implement the Bacon encoding algorithm. The file includes some comments that give some high level pseudo-code to get you started.

- **baconDecode.c** - The start of the program to decode the encoded text and recover the raw text. You will need to edit this file to implement the Bacon decoding algorithm. Ths file includes some comments that give some high level pseudo-code to get you started.

- **test.txt** - Some arbitrary raw text to try out your encode and decode programs.

- **Makefile** - A make file to simplify building and testing your code. It includes targets to make the baconEncode and baconDecode programs, as well as `test` and `clean` targets.

## Coding the project

Your job is to code and test the code in `baconEncode.c` and `baconDecode.c` using the variables provided in `baconCode.h`, and the algorithm described in the comments and in this file. You may use anything from the C library code, but I've highlighted the library code I used in the hints below.

## Hints and Suggestions

1. I found it easiest to do most of the standard input and output I/O one character at a time using `getchar` and `putchar`.

2. You may use `feof(stdin)` to check to see if you have reached the end of file for standard input. Or (and), if you have read a character into an `input` variable, you can use `(input==EOF)` to test for the end of file from standard input.

3. You may use `toLower(input)` to convert a single input character to lower case. Don't forget to include `ctype.h`.

4. To look up a character in a string, you can use `char * foundPtr=strchr(string,input)`. This will return a pointer to the first instance of `input` in `string`, where `input` is a single character, and `string` is an array of characters (or pointer to a list of characters.) If `input` is not present in `string`, this will return a NULL pointer. For non-null results, you can use pointer arithmetic: `foundPtr-string` to get the index of `input` in `string`. Don't forget to include `string.h`.

5. Use the `rand()` function to return a random integer value between 0 and `RAND_MAX`, where `RAND_MAX` is guaranteed to be at least 32,767 (the largest positive two's complement integer that fits in 16 bits), but may be larger. To get a random number evenly distributed between 0 and `N-1`, where `N` is an integer value less than `RAND_MAX`, use the remainder function `rand()%N`. For example, to get a random number between 1 and 8, use `1+rand()%8`. Or, to get a random value in a string, use `string[rand()%strlen(string)]`.

6. I have included the line of code `srand(time(0));` in baconEncode.c to "seed" the random number generator with the current time. This means that every time you run baconEncode, you will get a different stream of random numbers when you invoke `rand()`. Ultimately, this is the correct behavior, but it can make debugging your code difficult. If you are debugging, you may want to comment out this line of code. Then you will get the same stream of random numbers every time you run baconEncode. Don't forget to remove the comment and restore the random seed when you are finished debugging your code.

7. In the baconDecode program, you may assume the input provided to you was produced by a valid encoding program. That means you can assume each character is either a new-line, a blank, a vowel, or a consonant. Since it's a lot faster to check for vowels than consonants because there are a lot fewer of them, the most efficient code checks for vowels, and assumes that anything not a new-line, blank, or vowel is a consonant.

8. Many editors and some download programs (especially web browser download programs) don't understand files such as `Makefile` which does not have a file type. Such software often automatically tacks on a `.txt` suffix. This causes the `make` command to no longer recognize the make rules; the make command is looking for `Makefile`, not `Makefile.txt`. The easiest way to fix this problem is to rename in UNIX using the `mv` command: `mv Makefile.txt Makefile`. 

9. The make test command runs the UNIX `diff` command to check to see if the raw input text matches the encoded and decoded result. The `-i` flag tells the diff command to ignore differences in the case of letters. So, unless the input file contains characters that are not in the Bacon alphabet (`alfa`), then if your code is correct, the diff command will not report any differences. Run `man diff` to find out more about the diff command.

## Submitting the Project

When you have finished coding and testing you baconEncode and baconDecode programs, make sure you do a final git commit and push to update your main git repository. Then, retreive the 16 digit git hash code either from browsing your updated repository on the web, or using the command `git rev-parse HEAD` on the command line. Paste the git hash code in the Brightspace PROJ01 assignment. You may resubmit as many times as you would like to. Only the last submission will be graded.

## Grading Criteria

Your repository will be downloaded onto an LDAP machine at the level corresponding to the hash code retrieved from Brightspace, and compiled and run using the Makefile. The project is worth 100 points, and the following deductions will occur:

- -100 if your code matches or is significantly similar to any other student's code.
- -80 If your code does not attempt to address the problem.
- -50 if baconEncode does not compile using the initial Makefile
- -50 if baconDecode does not compile using the initial Makefile
- -10 if baconEncode has warning messages using the initial Makefile
- -10 if baconDecode has warning messages using the initial Makefile

If the correct results are not produced for make test, the TA will try to fix your code. For each fix, there will be a deduction of -15. If the TA cannot fix your code, or if you code requires more than 4 fixes, you will get a -60 deduction.

If your code passes the make test, we will run two further tests... We will run your baconDecode program on encoded text produced by the professor, and we will run the result of your baconEncode through the professor's baconDecode program, using an unpublished raw text that contains only characters from the valid alphabet. If either of these tests produces incorrect results, a further -10 points will be deducted. (That's a -20 deduction of both tests fail.)

There will also be a -10 point deduction each 24 hours (or part of 24 hours) the assignment is late, up to 5 days. After 5 days, there will be a -100 deduction.

