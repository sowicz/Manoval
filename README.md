# 📌 Aplikacja konsolowa C++ z OpenCV – wykrywanie wskazówki manometru

## 🎯 Cel
Aplikacja służy do automatycznego odczytu wskazań manometru na podstawie obrazu.  
Wykorzystuje bibliotekę **OpenCV** do przetwarzania obrazu i analizy położenia wskazówki.  
Wynikiem działania programu jest określenie, w której z **4 stref** znajduje się wskazówka.

---

## ⚙️ Funkcjonalności
- Wczytywanie obrazu manometru (z pliku lub kamery).
- Wstępne przetwarzanie obrazu:
  - konwersja do skali szarości,
  - redukcja szumów (np. GaussianBlur),
  - detekcja krawędzi (Canny).
- Wykrywanie okręgu tarczy manometru (transformacja Hougha).
- Detekcja wskazówki:
  - wyszukiwanie linii (HoughLinesP),
  - wybór najdłuższej linii wychodzącej ze środka tarczy.
- Obliczanie kąta wskazówki względem osi odniesienia.
- Podział tarczy na **4 strefy** (po 90° każda).
- Zasada wyboru strefy:
  - jeśli wskazówka jest pomiędzy strefami → przyjmowana jest **niższa wartość**.
- Wynik w konsoli: numer strefy (1–4).

---

## 🖥️ Przykładowy przebieg działania
1. Uruchomienie programu:
   ```bash
   ./manometr_detector obraz.jpg

2.Analiza obrazu i wykrycie wskazówki.

3.Obliczenie kąta wskazówki.
4.Podział tarczy:
- Strefa 1: 0°–90°
- Strefa 2: 90°–180°
- Strefa 3: 180°–270°
- Strefa 4: 270°–360°

5. Wynik:
```bash
Wskazówka znajduje się w strefie: 2
