#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compare_string (char* a, char* b){
    if (strlen (a) != strlen(b)){
        return 0;
    }else{
        for (int i = 0; i < strlen(a); i++){
            if (a[i] != b[i]){
                return 0;
            }
        }
        return 1;
    }
}

int main(){
    char* a = malloc(sizeof(char)* 12);
    char* b = malloc(sizeof(char)* 25);
    strcpy(a, "bonjour");
    strcpy(b, "bonjour");
    printf("%d\n", compare_string(a,b));
    printf("%d\n", strcmp(a, b));
    return 0;
}