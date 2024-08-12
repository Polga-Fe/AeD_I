#include <stdio.h>
#include <stdbool.h>

#define MAX 5

bool lemonadeChange(int* bills, int billsSize) {
    int nota_5 = 0;
    int nota_10 = 0;

    for (int i = 0; i < billsSize; i++) {
        if (bills[i] == 5) {
            nota_5++;
        } else if (bills[i] == 10) {
            if (nota_5 == 0) {
                return false;
            }
            nota_5--;
            nota_10++;
        } else if (bills[i] == 20) {
            if (nota_10 > 0 && nota_5 > 0) {
                nota_10--;
                nota_5--;
            } else if (nota_5 >= 3) {
                nota_5 -= 3;
            } else {
                return false;
            }
        }
    }

    return true;
}

void testLemonadeChange() {
    bool resp1;
    int j;

    int bills1[MAX];
    for (j=0;j<MAX;j++){
        printf("DIGITE O VALOR %d: ", j+1);
        scanf("%d",&bills1[j]);
    };
    printf("VALORES RECEBIDOS: ");
    for (j=0;j<MAX;j++){
        printf(" %d ",bills1[j]);
    }
    printf("\n");

    int billsSize1 = sizeof(bills1) / sizeof(bills1[0]);
    resp1 = lemonadeChange(bills1, billsSize1);
    printf("%s\n",resp1 ? "true" : "false");
}

int main(){
    testLemonadeChange();
    return 0;
}