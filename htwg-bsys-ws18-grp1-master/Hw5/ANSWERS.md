# ANSWERS

## Frage1

Es ändert sich:
Die Größe des nicht verwendeten Speichers (free)
Gesendete Blöcke (bo)
Die Nummer der Interrupts (in)
Die Nummer der Context Switches (cs)
Die Zeit die für "non-kernel-code" benutz wird (us)
Die Idle-Time (id)

Umso mehr prozesse von ./mem gleicheztig laufen, desto deutlischer werden die oben genangen Veränderungen.

## Frage2

Der swpd-Wert beginnt mit dem wert 24684 und free auf 451792. Nach beginn des Programmes steigt der swpd-Wert auf 24704 und verbleibt dort, der free-Wert steigt dabei allerdings auf bis zu >72000. Bei beendigung des Programmes steigt der free-Wert auf >1110000 da alles freigegeben wird.

## Frage3


MemTotal:        2097152 kB
MemFree:         1115192 kB
MemAvailable:    1622316 kB

Ca. 1,6 Gb verfügbar.

Bei kleinen Datenmengen wie bei ./mem 400 verändert sich bei den swaps nicht viel. Erhöhen wir die Datenmenge und gehen an die Grenze des vorhandenen Speichers so steigen die si und so werte schnell stark. Bei jedem Loop-Durchlauf, falls dieser überhaupt ausgeführt wird, steigt sehr stark.

Übersteigen wir den Speicher terminiert sich das Programm.

## Frage4

Analog zu Frage3 steigen die IO-Werte bei jedem Schleifendurchlauf.

## Frage5

./mem 1500

allocating 1572864000 bytes (1500.00 MB)
  number of integers in array: 393216000

<p>loop 0 in 1253.37 ms (bandwidth: 1196.77 MB/s)<br>
loop 1 in 525.60 ms (bandwidth: 2853.87 MB/s)<br>
loop 2 in 540.28 ms (bandwidth: 2776.35 MB/s)<br>
loop 3 in 509.32 ms (bandwidth: 2945.10 MB/s)<br>
loop 4 in 560.04 ms (bandwidth: 2678.39 MB/s)<br>
loop 5 in 540.72 ms (bandwidth: 2774.08 MB/s)<br>
loop 6 in 525.44 ms (bandwidth: 2854.77 MB/s)<br>
loop 7 in 528.35 ms (bandwidth: 2839.05 MB/s)<br>
loop 8 in 466.39 ms (bandwidth: 3216.16 MB/s)<br>
loop 9 in 549.42 ms (bandwidth: 2730.18 MB/s)<br>
loop 10 in 540.36 ms (bandwidth: 2775.94 MB/s)</p>

./mem 4000

allocating 4194304000 bytes (4000.00 MB)
  number of integers in array: 1048576000
  
loop 0 in 35582.96 ms (bandwidth: 112.41 MB/s)

Wenn wir mehr Speicher verwenden braucht ein Schlifendurchlauf länger und somit verringert sich die Bandbreite. Passen die gewünschten Daten in den Speicher kommt es selten zu einem swap, was sich bei zu großen Datenmengen allerdings ändert.

Der Graph würde exponentielles Wachstum zeigen.

## Frage6
Wenn man versucht mehr Speicher anzufordern wird ein teil auf den swapspeicher ausgelagert. Wird allerdings mehr als normaler + swapspeicher versucht zu reservieren, müsste das Programm in einen Timeout laufen bzw. vom OS gekillt werden.

## Frage7
Swapping kann sehr effektiv sein wenn man mit großen Daten arbeitet die allerdings selten benutzt werden. Somit kann man eben diesen auf ein anderes Device auslagern und wenn nötig wieder von dort holen. Verweißt man den Swap darauf ist dies auch performanter als es von einem "normalen" Speicher zu holen.
