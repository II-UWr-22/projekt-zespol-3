# Bot do szachów - projekt na PWI

Bot jest silnikiem (engine) do programu XBoard, stanowiącego interfejs użytkownika.

## Wymagania

* g++ (instalacja na Ubuntu: `sudo apt install g++`) (przetestowana wersja to 11.3.0)
* XBoard (instalacja na Ubuntu:`sudo apt install xboard`) (przetestowana wersja to 4.9.1)

## Kompilacja i uruchomienie

```
git clone https://github.com/II-UWr-22/projekt-zespol-3.git
cd projekt-zespol-3
g++ src/*.cpp -o engine
xboard -fcp ./engine
```

Projekt został przetestowany na Ubuntu 22.04.1 LTS.

---

[Dokument z planem](https://docs.google.com/document/d/1fXRxu2YtP9Zh2NFL-WkHxfGKPPq2pbr_ReeQp045GxE/edit?usp=sharing)
