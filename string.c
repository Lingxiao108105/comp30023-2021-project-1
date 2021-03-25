#include <stdio.h>

#include "string.h"

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

/**transfer a string into interger
 * will stop when meet a non-numeric character
 * return -1 when first char is a non-numeric char
 * cannot recognize a negative number(not necessary for this project)
*/
int atoi(char *s){
    int length = strlen(s);
    int i = 0;
    //the number we want
    int num=-1;
    //check whether the first char is a number
    if(s[0]>47 && s[0]<58){
        num=0;
    }
    for(i=0;i<length;i++){
        if(s[i]>47 && s[i]<58){
            num = num*10 + s[i]-48;
        }
    }
    return num;
}