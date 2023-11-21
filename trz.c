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

    // Liczymy min:
    // Będziemy iterować po hotelu a. Dla tego hotelu szukamy najdłuższego
    // podciągu kolejnych tych samych moteli, po znalezieniu ich iterujemy po
    // nich i szukamy minimum. Na końcu przerzucamy a na przedostatni motel
    // w podciągu.
    int min = INT_MAX;

    for(int a = 0; a < n - 2; a++){
        // jeżeli dwa pod rząd a są te same możemy ten pierwszy pominąć
        if(motele[a].siec == motele[a + 1].siec)
            continue;

        for(int x = a + 1; x < n; x++){
            // jeżeli trafimy na motel tej samej sieci co nasz a, oznacza to
            // że nie ma żadnej sensownej trójki więc możemy pominąć wartości
            if(motele[a].siec == motele[x].siec){
                a = x-2;
                break;
            }

            if(motele[x].siec != motele[a + 1].siec){
                for(int i = a + 1; i < x; i++){
                    // te wartości się zwiększają, więc możemy break'ować
                    if(motele[i].odl - motele[a].odl >= min)
                        break;
                    // te wartości się zmniejszają, czyli continue
                    if(motele[x].odl - motele[i].odl >= min)
                        continue;

                    min = MAX(motele[i].odl - motele[a].odl, 
                              motele[x].odl - motele[i].odl);
                }
                // uwzględniamy że pętla zwiększy a o jeden
                a = x-2;
                break;
            }
        }
    }
    // jeśli są tylko dwie/jedna sieci to nie zmieni się to min = INT_MAX więc
    // wtedy wyrzucamy "0 0", i zwalniamy pamięć.
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

    // Liczymy max:
    // początkowo wyznaczmy trzy_pierwsze i trz_ostatnie, czyli tablice z
    // trzema pierwszymi różnymi elementami i trzema ostatnimi różnymi
    // elementami. One pozwalają nam dla każdego elementu sprawdzić dla każdego
    // środkowego elementu dwa skrajne różne, czyli zmaksymalizuje odległości.
    int max = 0;
    int trzy_pierwsze[3] = {0, 0, 0};
    int trzy_ostatnie[3] = {n - 1, n - 1, n - 1};
    int i = 1;

    for(int j = 0; j < n; j++){
        if(motele[j].siec != motele[trzy_pierwsze[0]].siec && 
           motele[j].siec != motele[trzy_pierwsze[1]].siec && 
           motele[j].siec != motele[trzy_pierwsze[2]].siec){
            trzy_pierwsze[i] = j;
            i++;
            if(i >= 3) break;
        }
    }
    i = 1;

    for(int j = n - 1; j > 0; j--){
        if(motele[j].siec != motele[trzy_ostatnie[0]].siec && 
           motele[j].siec != motele[trzy_ostatnie[1]].siec && 
           motele[j].siec != motele[trzy_ostatnie[2]].siec){
            trzy_ostatnie[i] = j;
            i++;
            if(i >= 3) break;
        }
    }
    // iterujemy po środkowych elementach
    for(int b = 1; b < n - 1; b++){
        for(int a = 0; a < 3; a++){
            // wartości się zmniejszają możemy break'ować
            if(motele[b].odl - motele[trzy_pierwsze[a]].odl <= max) break;
            // wartości się zwiększają , czyli continue
            if(motele[b].siec == motele[trzy_pierwsze[a]].siec) continue;

            for(int c = 0; c < 3; c++){
                // zmniejszają
                if(motele[trzy_ostatnie[c]].odl - motele[b].odl <= max) break;
                // zwiększają, i sprawdzamy czy motele z różnych sieci
                if(motele[b].siec == motele[trzy_ostatnie[c]].siec ||
                   motele[trzy_ostatnie[c]].siec == motele[trzy_pierwsze[a]].siec) 
                    continue;

                max  = MIN(motele[trzy_ostatnie[c]].odl - motele[b].odl, 
                           motele[b].odl - motele[trzy_pierwsze[a]].odl);
            }            
        }
    }
    // wypisujemy, i uwalniamy pamięć
    printf("%d %d", min, max);
    free(motele);
    return 0;
}