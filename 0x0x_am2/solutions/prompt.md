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

Trage deine Antworten in folgendes **JSON**-Format ein. Dabei gibt es je Aufgabe und Teilaufgabe 
aus dem Scoring einen Eintrag in einem Ergebnis-Objekt mit den Schlüsseln "Aufgabe.Teilaufgabe" 
und jeweils einem Objekt (in das Du etwas einträgst) bestehend aus den Punkten ("Punkte") 
und dem Kommentar ("Kommentar") mit den Hinweisen zur Bewertung der jeweiligen Aufgabe und Teilaufgabe.
Ganz am Ende summiere die Punkte und trage sie in das Feld "Gesamtpunkte" ein.
Nutze genau dieses Format und ersetze jeweils nur die Werte.

{
    "Ergebnis": {
        "A1.a": {
            "Punkte": 0,
            "Kommentar": ""
        },
        "A1.b": {
            "Punkte": 0,
            "Kommentar": ""
        },
        "A2.a": {
            "Punkte": 0,
            "Kommentar": ""
        },
        "A2.b": {
            "Punkte": 0,
            "Kommentar": ""
        },
        "A2.c": {
            "Punkte": 0,
            "Kommentar": ""
        },
        "A2.d": {
            "Punkte": 0,
            "Kommentar": ""
        },
        "A2.e": {
            "Punkte": 0,
            "Kommentar": ""
        },
        "A2.f": {
            "Punkte": 0,
            "Kommentar": ""
        },
        "A2.g": {
            "Punkte": 0,
            "Kommentar": ""
        },
        "A2.h": {
            "Punkte": 0,
            "Kommentar": ""
        },
        "A3.a": {
            "Punkte": 0,
            "Kommentar": ""
        },
        "A3.b": {
            "Punkte": 0,
            "Kommentar": ""
        },
        "A3.c": {
            "Punkte": 0,
            "Kommentar": ""
        },
        "A3.d": {
            "Punkte": 0,
            "Kommentar": ""
        },
        "A3.e": {
            "Punkte": 0,
            "Kommentar": ""
        },
    },
    "Gesamtpunkte": 0
}


# Scoring

Aufgabe A1

A1.a) 2P:
- Attribut mit korrektem Typ und Namen 1P
- default ctor 1P

A1.b) 8P:
- Setter 1P
- Getter 1P
- const ref& für string Parameter in Setter 1P
- config& als Rückgabe Setter 1P
- const in Signatur 1P
- Ausgabeoperator-Funktionalität 1P
- const ref& für config Parameter in Ausgabeoperator 1P
- 'friend' in der Klasse genutzt 1P

Aufgabe A2

A2.a) 2P:
- Typdefinition 2P

A2.b) 4P:
- Basisklasse mit rein virtuellen Funktionen input,process,output 2P
- IPO& als Rückgabe 1P
- virtueller Destruktor 1P

A2.c) 1P:
- IHK öffentlich abgeleitet 1P

A2.d) 2P:
- ctor mit const& config 1P
- nutzen der Member-Initialiser-List 1P

A2.e) 3P:
- protected verwendet 1P
- Attribute input_data_ vom Typ vector_t 1P
- Attribute output_data_ vom Typ vector_t 1P

A2.f) 4P:
- korrektes Überführen der Zahlen in den Vektor input_data_ 4P

A2.g) 2P:
- quadrieren der Werte zu output_data_ 2P

A2.h) 2P:
- Ausgabe in der Form `[y0,y1,…,y_size-1]` 2P

Aufgabe A3

A3.a) 3P:
- Klasse clever_ptr angelegt 1P
- raw ptr p mit korrektem Typ angelegt und initialisiert 2P

A3.b) 3P:
- Member-Initializer-List verwendet 1P
- new verwendet und initialisiert 1P
- Destruktor gibt Speicher frei 1P

A3.c) 1P
- copy-ctor gelöscht 1P

A3.d) 2P:
- korrekte Rückgabe mit int& 2P

A3.e) 1P
- korrekte Implementierung 1P


# Aufgabenstellung

### A1 [10P]

Erstellen Sie eine Klasse `config`, die der Konfiguration unseres Programmes dient
und exemplarisch einen Dateinamen zum Einlesen einer Datei enthält.

a) [2P] Statten Sie die Klasse `config` mit einem Default-Konstruktor und einem
privaten Attribute `file_name_` vom Typ `string` aus.

b) [8P] Implementieren Sie einen Setter `file_name`, einen Getter `file_name`,
und einen Ausgabeoperator als Freund der Klasse so, dass der folgende Testcode
in `main` funktioniert.
```
    // A1, Ausgabe: "cfg={'data.txt'}, filename='data.txt'"
    const auto name = "data.txt";
    const auto cfg = config().file_name(name);
    cout << "cfg={'" << cfg << "'}, filename='" << cfg.file_name() << "'" << endl;
```

---

### A2 [20P]

Ziel dieser Aufgabe ist ein Programm, welches nach dem EVA-Prinzip Daten verarbeitet.
Benötigt wird

a) [2P] ein Datentyp `vector_t` als Vektor von `int`.

b) [3P] und eine Basisklasse `IPO` (=EVA) mit drei *rein virtuellen Funktionen*
`input`, `process` und `output`.
Die Funktionen haben keine Parameter und der Rückgabetyp ist jeweils eine
Referenz auf sich selbst, also vom Typ `IPO`. Beachten Sie auch die 'Best Practices'
bei Klassen mit virtuellen Funktionen.

Von dieser Basisklasse wird die Klasse `IHK` abgeleitet, genauer:

c) [1P] `IHK` erbt öffentlich von `IPO`.

d) [3P] Der Konstruktor wird mit einem `config`-Objekt (aus A1) aufgerufen und
kopiert dieses in ein privates Attribut `cfg_` gleichen Typs.
<br>**Tipp:** Falls Ihre Klasse `config` aus *A1* nicht existiert oder fehlerhaft ist,
nutzen Sie einen `string`.

e) [3P] Die Klasse besitzt zwei weitere Attribute `input_data_` und `output_data_`
vom Typ `vector_t`, die in abgeleiteten Klassen sichtbar sind, aber nicht öffentlich.

f) [4P] Die Funktion `input` lädt eigentlich Zahlenfolgen aus einer Datei (deswegen `cfg_`).
Um es hier etwas einfacher zu gestalten, nutzen Sie statt eines File-Streams einen
fest codierten String-Stream (innerhalb von `input`)
```
    std::stringstream data{string("1,3,10,2,2")};
```
und überführen die Zahlen in den Vektor `input_data_`.

<br>**Tipps:**
- Falls die Überführung fehlerhaft ist, füllen Sie den Vektor `input_data_` direkt mit
  den Werten `1,3,10,2,2`.
- Nutzen Sie `std::stoi(string)` zur Umwandlung eines Strings in einen `int`.

g) [2P] Die Funktion `process` quadriert jeden Wert aus `input_data_` und füllt so den
Vektor `output_data_`.

h) [2P] Die Funktion `output` gibt `output_data` in der Form `[1,9,100,4,4]` aus
(genau so).

Testen können Sie die Klasse mit diesem Code:
``` 
    // A2, Ausgabe: "[1,9,100,4,4]"
    IHK(config().file_name("file")).input().process().output();
```

Die folgende Ergänzung müssen Sie nicht bearbeiten, sie dient lediglich dazu aufzuzeigen,
wie diese Aufgabe noch erweitert werden könnte, wenn wir die Themen 'Funktionszeiger' und
'Lambdas' kennengelernt haben.

Erweitern Sie das Interface um eine Funktion `process` mit einem Funktionszeigerparameter
und rufen Sie diese Funktion anstelle des Quadrierens auf. Testen Sie die Funktion mit
einem Lambda-Ausdruck.

---

### A3 [10P]

Angenommen, die Konfiguration `config` enthält sehr viele Einstellungen. Dann sollen
die Daten unter der Verwendung von dynamischem Speicher und 'Smart'-Pointern angelegt werden.
Leider ist die Klasse `unique_ptr` nach Auskunft von *ChatGPT* buggy (stimmt das? wir wissen
es gerade nicht) und Sie verwenden daher lieber eine kleine eigene Implementierung
namens `clever_ptr`.

a) [3P] Legen Sie eine Klasse `clever_ptr` an, die einen privaten (raw)Zeiger `p_` auf
eine Instanz vom Typ `int` enthält. Dieser wird mit `nullptr` initialisiert.

b) [3P] Ergänzen Sie die Klasse um einen Konstruktor, der dynamisch vom Heap einen `int`
allokiert und mit dem übergebenen `int` initialisiert, sowie um einen Destruktor, der den
Speicher wieder freigibt.

c) [1P] 'Löschen' Sie den Copy-Konstruktor.

d) [2P] Die Funktion `get` gibt eine konstante Referenz auf die Instanz in `p` zurück.

e) [1P] Implementieren Sie zusätzlich zu `get` den Dereferenzierungsoperator `*`
mit der gleichen Funktionalität wie `get`, siehe Code.

Testen können Sie die Klasse mit diesem Code:
``` 
    // A3, Ausgabe: "cp.get()=42, *cp=42"
    const auto cp = clever_ptr(42);
    cout << "cp.get()=" << cp.get() << ", *cp=" << *cp << endl;
```

Die folgende Ergänzung müssen Sie nicht bearbeiten, sie dient lediglich dazu aufzuzeigen,
wie diese Aufgabe noch erweitert werden könnte.

Überführen Sie die Klasse in eine generische Klasse, sodass nicht nur `int` verwendet
werden können.

---

Achten Sie auf `const`, wenn möglich, und nutzen Sie `auto` bzw. `auto&` und
range-based for, wenn sinnvoll.

---

Ende der Aufgabenstellung

