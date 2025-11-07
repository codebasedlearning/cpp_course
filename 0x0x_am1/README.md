[© 2025, A.Voß, FH Aachen, codebasedlearning.dev](mailto:info@codebasedlearning.dev)

Note: This is part of a test exam task, which is why it is given in German.

# Tasks – Exam 1

---

Zeit: 1h, Punkte: 60, Bonus 2

---

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
und dann die globale Variable um eins erhöht. Die Funktion ist dafür zuständig,
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

Falls die ID größer als die `max_id` ist, werfen Sie einen `runtime_error` 
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

---

End of `Tasks – Exam 1`
