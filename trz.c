#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>

int min(int a, int b){
    if(a < b){return a;}
    else{return b;}
}

int max(int a, int b){
    if(a > b){return a;}
    else{return b;}
}

/*Zwraca odległość najdalszej trójki moteli różnych sieci */
int min_trzy_rozne(int siec[], int odl[], unsigned n){
    int mini = INT_MAX;
    unsigned pierwszy = 0;
    unsigned i = 1;
    while(siec[i] == siec[pierwszy]){pierwszy++; i++;}
    unsigned srodkowy_p = i;
    unsigned srodkowy_o = i;
    i++;
    while(i < n){
        //jeśli trzy różne sieci
        if(siec[i] != siec[pierwszy] && siec[i] != siec[srodkowy_p]){
            for(unsigned j = srodkowy_p; j <= srodkowy_o; j++){
                mini = min(mini, max(odl[j] - odl[pierwszy], odl[i] - odl[j]));
            }
            pierwszy = srodkowy_o;
            srodkowy_p = i;
            srodkowy_o = i;
        }
        //jeśli ta sama co wcześniej
        else if(siec[i] == siec[pierwszy]){
            pierwszy = srodkowy_o;
            srodkowy_p = i;
            srodkowy_o = i;
        }
        else if(siec[i] == siec[srodkowy_p]){
            srodkowy_o++;
        }
        else{
            return -1;
        }
        i++;
    }
    return mini;
}

/*Zwraca minimalną ogległość pomiędzy trzema motelami różnych sieci lub -1 gdy sieć się powtarza*/
int min_odleglosc(int siec[], int odl[], unsigned a, unsigned b, unsigned c){
    if(siec[a] == siec[b] || siec[b] == siec[c] || siec[c] == siec[a]){return -1;}
    return(min(odl[b] - odl[a], odl[c] - odl[b]));
}

/*Zwraca tablicę n początkowych indeksów moteli, które należą do różnych sieci
(jeśli nie ma tylu różnych indeksów, pozostałe są wypełnione wartością UINT_MAX) */
unsigned* poczatkowe_rozne_sieci(int siec[], unsigned rozmiar, unsigned n, bool odwrocone){
    unsigned* tab = (unsigned*) malloc(n * sizeof(unsigned));
    for(unsigned i = 0; i < n; i++){tab[i] = UINT_MAX;}

    unsigned licznik_roznych = 0;
    bool powtorka;
    unsigned iter;
    for(unsigned i = 0; i < rozmiar && licznik_roznych < n; i++){
        //Ustawienie iteratora
        if(odwrocone){
            iter = rozmiar - 1 - i;
        }
        else{
            iter = i;
        }
        //Sprawdzenie czy różny
        powtorka = false;
        for(unsigned j = 0; j < licznik_roznych; j++){
            if(siec[tab[j]] == siec[iter]){
                powtorka = true;
                break;
            }
        }
        //Dodanie gdy różny
        if(!powtorka){
            tab[licznik_roznych++] = iter;
        }
    }
    return tab;
}

/*Zwraca odległość najbliższej trójki moteli różnych sieci */
int max_trzy_rozne(int siec[], int odl[], unsigned n){
    unsigned* pierwsze_rozne_sieci = poczatkowe_rozne_sieci(siec, n, 3, false);
    unsigned* ostatnie_rozne_sieci = poczatkowe_rozne_sieci(siec, n, 3, true);
    
    //rozmiar = liczba realnych indeksów w tablicy pierwsze_rozne_sieci
    unsigned rozmiar = 0;
    for(int i = 0; i < 3; i++){
        if(pierwsze_rozne_sieci[i] != UINT_MAX){
            rozmiar++;
        }
    }

    int maxi = -1;

    /*Iteracja po każdej kombinacji początkowych i końcowych wartości oraz wszystkich pozostałych*/
    for(unsigned i = 0; i < rozmiar; i++){
        for(unsigned j = 0; j < rozmiar; j++){
            for(unsigned k = 0; k < n; k++){
                maxi = max(maxi, min_odleglosc(siec, odl, pierwsze_rozne_sieci[i], k, ostatnie_rozne_sieci[j]));
            }
        }
    }
    
    free(pierwsze_rozne_sieci);
    free(ostatnie_rozne_sieci);
    
    return maxi;
}

int main(){
    unsigned n;
    scanf("%u", &n);

    int* siec = malloc(sizeof(int) * n);
    int* odl = malloc(sizeof(int) * n);

    for(unsigned i = 0; i < n; i++){
        scanf("%d %d", &siec[i], &odl[i]);
    }

    int mini = min_trzy_rozne(siec, odl, n);
    int maxi = max_trzy_rozne(siec, odl, n);

    if(maxi == -1){
        //Gdy nie ma 3 różnych elementów
        printf("%d %d\n", 0, 0);
    }
    else{
        printf("%d %d\n", mini, maxi);
    }
}
