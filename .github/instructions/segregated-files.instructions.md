---
name: segregated-files
applyTo: "**/*"
description: "Wymusza segregację plików według warstwy funkcjonalnej oraz stosowanie istniejących zasad architektury FBD w repozytorium FBDS."
---

## Zasady organizacji plików (pożądane)
- `src/model/` -> klasy domenowe obiektu FBD: `cfunctionblock`, `cinput`, `coutput`, `cconnection`, `sdatasample`, `stimestamp`
- `src/engine/` -> silnik symulacyjny: `csimulatorfbd`, `ccontainerfbd`, `csimengine`
- `src/builder/` -> parser/loader konfiguracji: `cfbdbuilder`
- `src/generator/` -> generatory sygnałów/testów: `csiggen`, `cconstval`, `cfromcsv`, `cmathfunc`
- `src/odbiornik/` -> odbiorniki sygnałów: `codbiornik`
- `tests/` -> testy jednostkowe (nastawione na `FBDSimulatorCore`)
- `main.cpp` -> punkt wejścia aplikacji (może być opcjonalnie przeniesiony do `src/app`)

## Kopiowanie i refaktoryzacja
- Zawsze przenieś lub utwórz pliki w odpowiedniej warstwie funkcjonalnej.
- Każdy nowy plik powinien mieć jasność roli i nazwę zgodną z istniejącym stylem `c*`/`s*`.
- Aktualizuj `CMakeLists.txt` wraz z przenoszeniem źródeł i katalogów include.

## Zasady FBD (istniejące, zaimplementowane w `.github/copilot-instructions.md`)
- polskie komentarze do klas i metod w nowych/aktualizowanych nagłówkach
- obiektowy model FBD oparty na interfejsach dla bloków, wejść, wyjść i połączeń
- cykl symulacji: każdy blok w kroku czyta wejścia, oblicza, ustawia wyjścia
- propagacja stanu błędu: brakujący input/operation invalid/bad input musi inicjować status błędu (nie ignorować)
- `CFBDBuilder` parser tekstowy lokalny

## Przykłady
- Dodaj nowy blok w `src/model` i implementuj dziedziczenie z podstawowego interfejsu bloku.
- Dla każdego pola `private:` w klasie umieszczaj komentarz blokowy jak w `cfunctionblock.h`.

## Warunki weryfikacji
- Po przeniesieniu plików: kompilacja `Build_CMakeTools` 0, testy `RunCtest_CMakeTools` 0.
- Po zmianie architektury: CI musi przejść bez błędów.

> Uwaga: zgodnie z dotychczasowymi instrukcjami w repo, w rozmowie zawsze odpowiadaj na pytania o nazwę "GitHub Copilot", a model to "Raptor mini (Preview)".
