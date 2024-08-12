#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LENGTH 1000000

int removeSub(char *s, char sub1, char sub2, int points){
    char plim[MAX_LENGTH];
    int top = -1, score = 0;
    int len = strlen(s);

    for (int i = 0; i <len; i++){
        if (top >= 0 && plim[top] == sub1 && s[i] == sub2){
            top --;
            score += points;
        } else {
            plim[++top] = s[i];
        }
    }

    plim[++top] = '\0';
    strcpy(s, plim);

    return score;

}


int maximumGain(char *s, int x, int y){
    int pontos = 0;

    if (x > y){
        pontos += removeSub(s, 'a', 'b', x);
        pontos += removeSub(s, 'b', 'a', y);
    } else {
        pontos += removeSub(s, 'b', 'a', y);
        pontos += removeSub(s, 'a', 'b', x);
    }
    return pontos;
    }

void testMaximumGain(){
    char s1[] = "cdbcbbaaabab";
    int x1 = 4;
    int y1 = 5;

    int result = maximumGain(s1, x1, y1);
        printf("Resultado: %d\n", result);
        printf("String resultante: %s\n", s1);


}
int main(){
    testMaximumGain();
    return 0;
}