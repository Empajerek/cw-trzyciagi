#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX(x,y) ((x) > (y)? (x) : (y))
#define MIN(x,y) ((x) < (y)? (x) : (y))

typedef struct Motel {
    int siec;
    int odl;
} Motel;

int main() {
    int n;
    scanf("%d", &n);

    Motel* motele = malloc((unsigned) n * sizeof(Motel));

    for (int i = 0; i < n; i++)
        scanf("%d %d", &motele[i].siec, &motele[i].odl); // wczytujemy motele

    int min = INT_MAX;

    for(int a = 0; a < n; a++){
        for(int b = a+1; b < n; b++){

            const int odlAB = motele[b].odl - motele[a].odl;

            if(odlAB >= min)
                break;

            if(motele[a].siec == motele[b].siec)
                continue;

            for(int c = b+1; c < n; c++){

                const int odlBC = motele[c].odl - motele[b].odl;

                if(odlBC >= min)
                    break;

                if(motele[c].siec != motele[b].siec && motele[c].siec != motele[a].siec)
                    min = MAX(odlAB, odlBC);
            }
        }
    }

    if(min == INT_MAX){
        printf("0 0");
        return 0;
    }

    /*
                  ....           ....           ....           ....
             ||             ||             ||             ||
         /"""l|\        /"""l|\        /"""l|\        /"""l|\
        /_______\      /_______\      /_______\      /_______\
        |  .-.  |------|  .-.  |------|  .-.  |------|  .-.  |------
         __|L|__| .--. |__|L|__| .--. |__|L|__| .--. |__|L|__| .--.
        _\  \\p__`o-o'__\  \\p__`o-o'__\  \\p__`o-o'__\  \\p__`o-o'_
        ------------------------------------------------------------
        ------------------------------------------------------------
    */

    int max = 0;

    for(int i = 0; i < n; i++){
        for(int j = n-2; j > i; j--){

            const int odlAB = motele[j].odl - motele[i].odl;

            if(odlAB <= max)
                break;

            if(motele[i].siec == motele[j].siec)
                continue;

            for(int k = n-1; k > j; k--){

                const int odlBC = motele[k].odl - motele[j].odl;

                if(odlBC < max)
                    break;

                if(motele[k].siec != motele[j].siec && motele[k].siec != motele[i].siec)
                    max = MIN(odlAB, odlBC);
            }
        }
    }

    printf("%d %d", min, max);

    free(motele);
    return 0;
}
