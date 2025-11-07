# Aufgabe

Du sollst eine C++-Prüfung bewerten. Dazu bekommst Du nachfolgend die Aufgabenstellung 
und ein Punkteschema für alle Teilaufgaben, dann eine abgegebene Lösung per Datei. 

- Bewerte die Lösung **streng nach dem vorgegebenen Punkteschema**, aber lies und analysiere 
den Code vor der Bewertung auf Vorkommen der geforderten Elemente und berücksichtige 
funktional gleichwertige Varianten. Beurteile immer nach der Semantik, nicht nach der exakten Syntax.
- Gehe **Teilaufgabe für Teilaufgabe** vor.
- Analysiere **jeden einzelnen Bewertungspunkt** und gib für jede Teilaufgabe:
    - die **vergebene Punktzahl**
    - eine **prägnante Begründung für gegebene Punkte**
    - eine **prägnante Begründung für abgezogene Punkte**
- Du darfst Punkte auch für einen Ansatz geben, aber nur, wenn ein Punkt auch sinnvoll
angefangen wurde und signifikante Inhalte enthält.

  
# Ergebnisformat

Trage deine Antworten in folgendes **JSON**-Format ein. Dabei gibt es je Teilaufgabe 
aus dem Scoring einen Eintrag in einem Ergebnis-Objekt mit den Schlüsseln "Teilaufgabe" 
und jeweils einem Objekt (in das Du etwas einträgst) bestehend aus den Punkten ("Punkte") 
und dem Kommentar ("Kommentar") mit den Hinweisen zur Bewertung der jeweiligen Teilaufgabe.
Ganz am Ende summiere die Punkte und trage sie in das Feld "Gesamtpunkte" ein.
Nutze genau dieses Format und ersetze jeweils nur die Werte.

{
    "Ergebnis": {
        "a": {
            "Punkte": 0,
            "Kommentar": ""
        },
        "b": {
            "Punkte": 0,
            "Kommentar": ""
        },
    },
    "Gesamtpunkte": 0
}

# Scoring

a) 3P:
- `index_type` 1P
- `value_type` 1P
- `vector_type` 1P
beides möglich: 'typedef' oder 'using'

b) 2P:
- global 0.5P,
- korrekter Typ 0.5P,
- korrekter Name 0.5P,
- korrekte Init. 0.5P

c) 2P:
- korrekter Rückgabetyp+keine Params 0.5P,
- korrekter Name 0.5P,
- korrekter Rückgabewert 0.5P,
- nur ein Befehl mit Inkrement 0.5P

d) 5P:
- Klasse `multi_set` 1P
- private Member 1P
- `map` korrekt in Namen und Typ: 1P
- `max_id` korrekt in Namen und Typ: 1P
- Defaultwert für max_id 1P

e) 4P:
- ctor vorhanden 1P
- member init-list 1P
- explicit 2P
  const nicht gefordert

f) 16P
- id mit korrektem Typ vorhanden 1P
- const Ref. mit korrektem Typ verwendet 3P
- Exception mit korrekter Bedingung, korrektem Typ und sinnvoller Meldung geworfen 3P
- Param. Liste korrekt kopiert, dabei range-based for und auto& oder Iteratoren verwendet 4P
- neuer oder veränderter Vektor geholt und eingefügt 4P
- Rückgabe korrekt 1P
  temp. Obj. beim Holen geduldet, dann Einfügen notwendig

g) 2P
- Funktion mit korrektem Typ (siehe f) ) verwendet 1P
- `make_id()` verwendet 1P

h) 4P Testcode:
- Instanzen angelegt 1P
- beide Varianten `add` verwendet 1P
- darunter einmal mit existierendem und mit neuem Vektor 1P
- Exception gefangen 1P

i) 10P:
- Param. korrekt 1P
- const verwendet 1P
- find mit Iterator verwendet 3P
- Rückgabe (end(),.second) korrekt 5P
  [[nodiscard]] optional
  return map[id]; funktioniert wg. const nicht

j) 2P Testcode:
- Abfrage existierende id, unbekannte id 2P

k) 2P:
- Rückgabe korrekt 1P
- const verwendet 1P

l) 2P (viele Vorlagen)
- Signatur stimmt, incl. const ref. 1P
- Ausgabe und loop mit korrektem Komma und Größe stimmen 1P
  Loop über Index bei vector auch ok

m) 4P:
- Signatur stimmt, incl. const ref. 1P
- Ausgabe korrekt (gleich Logik) 3P

n) 2P Bonus:
- Die Funktion gibt eine Referenz auf eine lokale Variable zurück (dangling reference),
  die nach Funktionsende zerstört ist (undefiniertes Verhalten).


# Aufgabenstellung

Es soll ein Container entworfen werden, der (jeweils) zu einer ID (einer Nummer)
einen Vektor von Strings verwaltet.
Auszugsweise soll implementiert werden, dass Elemente zu einer ID hinzugefügt
oder abgefragt werden können.

---

Die folgenden Teilaufgaben können der Reihe nach umgesetzt werden. Wenn Sie
an einer Stelle nicht weiter wissen, überlegen Sie sich eine Alternative.
Zum Teil sind Alternativen angegeben, sodass Sie die Bearbeitung fortsetzen
können.

---

a) [3P] Definieren Sie drei eigene Datentypen:
- `index_type` ist ein `unsigned int`,
- `value_type` ist ein `string`,
- `vector_type` ist ein `vector` von `value_types`.
  Wenn Sie nicht wissen, wie das geht, verwenden Sie die angegebenen Typen
  direkt, also ohne Extradefinition.

b) [2P] Definieren Sie eine globale Variable `next_id` vom `index_type` und
initialisieren Sie sie mit 1.

c) [2P] Definieren Sie eine globale Funktion `make_id`, die `next_id` zurückgibt
und die globale Variable um eins erhöht. Die Funktion ist dafür zuständig,
eine Art eindeutige ID zu generieren. Sie hat keine Parameter und soll möglichst
effizient programmiert sein.

d) [5P] In der zu definierenden Klasse `multi_set` gibt es zwei private Membervariablen:
- `map` vom Typ `unordered_map` mit den beiden Template-Argumenten `index_type`
  und `vector_type`, und
- `max_id` vom Typ `index_type` mit Defaultwert 0.

`map` kann so zu einem Index, d.h. einer ID, einen Vektor von Strings assoziieren
und `max_id` gibt die maximale ID an, die wir zulassen wollen.

e) [4P] Definieren Sie einen Konstruktor mit einem `index_type` Parameter `max_id`
und initialisieren Sie den gleichnamigen Member damit.

Achten Sie auch darauf, dass etwaige Umwandlungen nicht implizit erfolgen können.

f) [16P] Definieren Sie eine Funktion `add`.
Diese Funktion soll unter einer ID in der Membervariablen `map` einen Vektor
von Strings hinzufügen (`vector_type`) bzw. erweitern, falls unter der ID schon
ein Vektor existiert.

Der erste Parameter der Funktion ist eine ID vom Typ `index_type` und der
zweite Parameter ein Vektor von Strings (s.o.).

Falls die ID größer oder gleich der `max_id` ist, werfen Sie einen `runtime_error`
und fügen keine Daten hinzu.

`add` gibt die ID zurück.

g) [2P] Definieren Sie eine zweite Funktion `add`, die nur den Vektor
übergeben bekommt und die Funktion `add` aus f) mit dem ersten Parameter
`make_id()` aufruft und diese ID somit auch zurückgibt.

h) [4P] Schreiben Sie zu e), f) und g) Testcode in `main`.

i) [10P] Definieren Sie eine Funktion `get`, die zu einer übergebenen ID
den zugehörigen Vektor findet und als Kopie zurückgibt. Ist unter dieser ID
kein Element vorhanden, gibt sie einen leeren Vektor zurück.

Nutzen Sie `map.find`.

j) [4P] Schreiben Sie zu i) Testcode in `main`.

k) [2P] Definieren Sie eine Funktion `size`, die die Anzahl von IDs
in `map` zurück gibt.

l) [2P] Implementieren Sie einen Ausgabeoperator für `vector_type`.

Die Ausgabe eines Vektors mit drei Beispielelementen sieht (genau) so
aus `['a','b','c']`.

m) [4P] Definieren Sie in der Klasse einen Ausgabeoperator für `multi_set`
und geben Sie die Größe und alle IDs mit assoziiertem Vektor aus.

Die Ausgabe mit zwei Beispielelementen sieht (genau) so
aus `(2){101->['a','b'],100->['Hello']}`.

n) [Bonus 2P]
Beschreiben Sie im Code in `main` in einem Satz, wo das Problem bei
der Funktion `sum_on_stack` liegt.

```
int& sum_on_stack(int n1, int n2) {
    int sum{n1+n2};
    return sum;
}
```

---

Achten Sie auf `const`, wenn möglich, und nutzen Sie `auto` bzw. `auto&` und
range-based for, wenn sinnvoll.

Ende der Aufgabenstellung

