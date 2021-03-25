#ifndef _STRING_H
#define _STRING_H


/**a basic library for String
*/


/** return the length of a string
*/
int strlen(char *s);
/**return 0 if two string are same
 * return 1 otherwise(different from <string.h>)
*/
int strcmp(char *s1, char *s2);
/**copy the second string into the first string
 * will not check whether s1 is big enough for s2!
*/
int strcpy(char *s1, char *s2);
/**transfer a string into interger
 * will stop when meet a non-numeric character
 * return -1 when first char is a non-numeric char
 * cannot recognize a negative number(not necessary for this project)
*/
int atoi(char *s);

#endif
