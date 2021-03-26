#ifndef _STRING_H
#define _STRING_H


/**a basic library for String
*/


/** return the length of a string
*/
int my_strlen(char *s);
/**return 0 if two string are same
 * return 1 otherwise(different from <string.h>)
*/
int my_strcmp(char *s1, char *s2);
/**copy the second string into the first string
 * will not check whether s1 is big enough for s2!
*/
int my_strcpy(char *s1, char *s2);

#endif
