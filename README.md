🎯 Opis aplikacji
Aplikacja konsolowa w języku C++ służy do automatycznego odczytu wskazań manometru na podstawie obrazu z kamery lub pliku graficznego. Wykorzystuje bibliotekę OpenCV do przetwarzania obrazu i analizy położenia wskazówki. Wynikiem działania programu jest określenie, w której z czterech zdefiniowanych stref znajduje się wskazówka manometru.

⚙️ Funkcjonalności
Wczytywanie obrazu manometru – z pliku lub kamery.
Wstępne przetwarzanie obrazu:
konwersja do skali szarości,
filtracja szumów (np. GaussianBlur),
detekcja krawędzi (Canny).
Wykrywanie okręgu tarczy manometru – np. za pomocą transformacji Hougha.

Detekcja wskazówki:
wyszukiwanie linii (HoughLinesP),
wybór najdłuższej linii wychodzącej ze środka tarczy.
Obliczanie kąta wskazówki względem osi odniesienia (np. poziomej).

Podział tarczy na 4 strefy:
każda strefa odpowiada 90° (pełne 360° podzielone na 4),
wskazówka przypisywana jest do odpowiedniej strefy.

Zasada wyboru strefy:
jeśli wskazówa znajduje się dokładnie na granicy lub pomiędzy strefami, aplikacja przyjmuje niższą wartość.
Wynik w konsoli – aplikacja wypisuje numer strefy (1–4).

🖥️ Przykładowy przebieg działania
Użytkownik uruchamia program podając ścieżkę do obrazu:

Kod
./manometr_detector obraz.jpg
Program analizuje obraz i wykrywa wskazówkę.

Oblicza kąt wkazówki względem osi odniesienia.
Dzieli tarczę na 4 strefy:
Strefa 1: 0°–90°
Strefa 2: 90°–180°
Strefa 3: 180°–270°
Strefa 4: 270°–360°

Wypisuje wynik:

Wskazówka znajduje się w strefie: 2
📌 Zastosowania
Automatyczny odczyt wartości manometrów w przemyśle.

Monitoring ciśnienia w instalacjach bez udziału człowieka.

Integracja z systemami SCADA lub IoT.
