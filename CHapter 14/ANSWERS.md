Antworten zur Simulation 1 in HW2
=================================

Quellcode + Makefile + Antworten vom Wintersemester17/18, eigene Gruppe.

Frage 1:
--------
Das Programm null.c erstellt einen Nullpointer auf einen Integer,
und versucht diesen über das return-statement zu dereferenzieren.
```c
//null.c
#include<stdlib.h>
int main()
{
  int *p = NULL;
  return *p;
}
```
Bei der Ausführung des Programms erhält man, logischerweise,
einen segmentation fault ( ~ keine Zugriffserlaubnis). Wir können nur Speicher auslesen der auch
tatsächlich zum Programm gehört und von diesem reserviert wurde.
Da unser pointer `*p` aber mit `NULL` initialisiert wurde,
gibt es keinen Speicher auf den wir zugreifen könnten.

Frage 2:
--------
Der debugger `gdb` gibt uns zusätzlich zum segfault, die Zeile aus in der dieser auftritt.
In unserem Fall war dies Zeile 6, `return *p;`.

Frage 3:
--------
`memcheck` liefert uns den Hinweis dass auf Adresse `0x0` zugegriffen wurde (bzw versucht),
diese aber nicht im gemappten Bereich liegt, also nicht stack'd, malloc'd oder free'd wurde.

Frage 4:
--------
Wir erstellen nun ein Programm das Speicher reserviert, aber nicht freigibt:
```c
//leak.c
#include<stdlib.h>
int main()
{
  int *p = malloc(sizeof(int));
  return 0;
}
```
Das Programm lässt sich ohne Probleme compilen und ausführen.
`gdb` lässt unser Programm normal durchlaufen.
Aus `memcheck` können wir jedoch ersehen, dass 1 mal Speicher allocated wurde (4 Byte weil Integer),
aber 0 mal free'd wurde. Daraus entsteht ein Speicherleck (memory leak),
welches im Abschnitt `leak summary` von `memcheck` genauer untersucht werden kann.
Dort ist ersichtlich, dass 4 Byte in 1 Block reserviert, aber nicht freigegeben wurden.

Frage 5:
--------
Wir schreiben ein kompilierbares, ausführbares Programm `array.c`:
```c
//array.c
#include<stdlib.h>
int main()
{
  int *data = malloc(100*sizeof(int));
  data[100] = 0;
  free(data);
  return 0;
}
```
`gdb` hilft uns nicht weiter. Doch in `memcheck` taucht ein Error auf (dank `-v` lesbar),
der uns verrät, dass wir auf nicht reservierten Speicher schreiben. Obwohl das Programm durchläuft,
sollten solche Speicherzugriffe vermieden werden. Man könnte unbeabsichtigt andere Daten überschreiben,
bzw falsche Daten lesen.

Frage 6:
--------
Das Programm aus Frage 5 wird nun so modifiziert, dass wir erst Speicher freigeben und dann darauf zugreifen:
```c
//free.c
#include<stdlib.h>
#include<stdio.h>
int main()
{
  int *data = malloc(100*sizeof(int));
  data[5] = 5;
  free(data);
  printf("%d\n", data[5]);
  return 0;
}
```
In `Valgrind` wird uns der unerlaubte Zugriff aufgeführt. Das Programm läuft trotzdem normal und scheint auch zu funktionieren.
Wir können auf den freigegebenen Speicher zugreifen, da dieser noch nicht wieder reserviert wurde.
Das sollte vermieden werden, da so undefiniertes Verhalten hervorgerufen werden kann.

Frage 7:
--------
Wenn wir `free()` nicht das ganze Array, sondern z.B. nur `&data[5]` übergeben, lässt sich das Programm zwar kompilieren, allerdings tritt ein Fehler zur Laufzeit auf, dass ein ungültiger Pointer an `free()` übergeben wurde. Es wird dazu eine Memory Map ausgegeben und das Programm bricht ab.

Frage 8:
--------
Wird `realloc()` für eine feste größe, und nicht elementeweiße, benutzt ist die performance relativ gut und "kostengünstig". Also kann man, wenn man weiß wie viele Elemente angefügt werden, die Funktion durchaus nutzen. Wird aber, wie bei einer Liste, die Liste Element für Element nach und nach angefügt ist die performance nicht gut.
