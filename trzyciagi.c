#include <stdio.h>
#include <stdlib.h>

#define MAX(x, y) ((x) > (y) ? (x): (y))
#define MIN(x, y) ((x) < (y) ? (x): (y))

int main(){
    int n = 0;
    scanf("%d", n);

    int** motels = malloc(n * sizeof(int*));
    for(int i = 0; i < n; i++){
        motels[i] = malloc(2 * sizeof(int));
    }
    int* corp = malloc(n * sizeof(int));
    memset(corp, 0, n * sizeof(int));
    int dist_corp = 0;

    for(int i = 0; i < n; i++){
        int corp_no;
        scanf("%d %d", corp_no, motels[i]);
        if(corp[corp_no -1] == 0){
            dist_corp++;
        }
        corp[corp_no - 1]++;
    }

    if(dist_corp < 3)
        printf("0 0");
    else {
        int max = 0, min = n;
    }

    return 0;
}