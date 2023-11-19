// rozwiązanie w O(n)

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

    // wczytujemy motele
    for (int i = 0; i < n; i++)
        scanf("%d %d", &motele[i].siec, &motele[i].odl);

    int min = INT_MAX;

    // Liczymy min:
    // dla każdej pary moteli a,b różnych sieci w odległości mniejszej 
    // od aktualne_min, szukamy motelu c, w odległości od b mniejszej
    // od aktualne_min, wtedy aktualne_min to max z tych odległości.
    for(int a = 0; a < n-2; a++){

        if(motele[a].siec == motele[a+1].siec)
            continue;

        for(int x = a+1; x < n; x++){

            if(motele[a].siec == motele[x].siec){
                a = x-1;
                break;
            }

            if(motele[x].siec != motele[a+1].siec){
                for(int i = a+1; i < x; i++){

                    if(motele[i].odl - motele[a].odl >= min)
                        break;
                    
                    if(motele[x].odl - motele[i].odl >= min)
                        continue;

                    min = MAX(motele[i].odl - motele[a].odl, motele[x].odl - motele[i].odl);
                    a = x-1;
                    break;
                }
            }
        }
    }

    // jeśli są tylko dwie/jedna sieci to nie zmieni się to min = INT_MAX więc wtedy wyrzucamy "0 0"
    if(min == INT_MAX){
        free(motele);
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

    // Liczymy max:
    // dla każdej pary moteli a,b różnych sieci w odległości większej 
    // od aktualne_max, szukamy motelu c, w odległości od b większej
    // od aktualne_max, wtedy aktualne_max to min z tych odległości.
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