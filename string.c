#include <stdio.h>

#include "./string.h"

/** return the length of a string
*/
int strlen(char *s){
    int i = 0;
    for(i=0;s[i]!=0;i++){};
    return i;
}

/**return 0 if two string are same
 * return 1 otherwise(different from <string.h>)
*/
int strcmp(char *s1, char *s2){
    int length = 0;
    int i = 0;
    if((length=strlen(s1))!=strlen(s2)){
        return 1;
    }

    for(i=0;i<length;i++){
        if(s1[i]!=s2[i]){
            return 1;
        }
    }

    return 0;
}

/**copy the second string into the first string
 * will not check whether s1 is big enough for s2!
*/
int strcpy(char *s1, char *s2){
    int length = strlen(s2);
    int i = 0;

    for(i=0;i<length;i++){
        s1[i] = s2[i];
    }

    return 0;
}
