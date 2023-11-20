#!/bin/bash
tests=0
while [ 1 ]; do
  tests=$(($tests+1))  # inkrementacja zmiennej
  echo -n "Test #$tests... "  # echo -n wypisuje bez newline
  echo "$test" | python3 gen.py > temp/p.in  # podajemy numer testu i parametry wywołania skryptu do generatora
  ./build/brute_trz.exe < temp/p.in > temp/p1.out
  ./build/trz.exe < temp/p.in > temp/p2.out
  check=`diff -w -q temp/p1.out temp/p2.out`  # diff sprawdza, czy pliki sie roznia;
                                    # opcja -w ignoruje biale znaki; opcja -q wypisuje tylko czy pliki sie roznia
  if [ "$check" != "" ]; then  # czy diff niepusty
    echo "FAILED"
    exit
  fi
  echo -n "OK "
  cat temp/p1.out | head -n 1  # Wypisuje pierwszy (tu akurat jedyny) wiersz wyniku bruta
  echo ""
done