[© 2025, A.Voß, FH Aachen, codebasedlearning.dev](mailto:info@codebasedlearning.dev)

Note: This is part of a test exam task, which is why it is given in German.

# Tasks – Exam 2

---

- Zeit 1h 15min, Punkte: 40

---

Die folgenden Teilaufgaben können der Reihe nach umgesetzt werden. Wenn Sie
an einer Stelle nicht weiter wissen, überlegen Sie sich eine Alternative.
Zum Teil sind Alternativen angegeben, sodass Sie die Bearbeitung fortsetzen
können.

---

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

b) [4P] und eine Basisklasse `IPO` (=EVA) mit drei *rein virtuellen Funktionen* 
`input`, `process` und `output`.
Die Funktionen haben keine Parameter und der Rückgabetyp ist jeweils eine 
Referenz auf sich selbst, also vom Typ `IPO`. Beachten Sie auch die 'Best Practices' 
bei Klassen mit virtuellen Funktionen.

Von dieser Basisklasse wird die Klasse `IHK` abgeleitet, genauer:

c) [1P] `IHK` erbt öffentlich von `IPO`.

d) [2P] Der Konstruktor wird mit einem `config`-Objekt (aus A1) aufgerufen und 
kopiert dieses in ein privates Attribut `cfg_` gleichen Typs.
<br>**Tipp:** Falls Ihre Klasse `config` aus *A1* nicht existiert oder fehlerhaft ist, 
nutzen Sie einen `string`.

e) [3P] Die Klasse besitzt zwei weitere Attribute `input_data_` und `output_data_` 
vom Typ `vector_t`, die in abgeleiteten Klassen sichtbar sind, aber nicht öffentlich.

f) [4P] Die Funktion `input` lädt eigentlich Zahlenfolgen aus einer Datei (deswegen `cfg_`).
Um es hier etwas einfacher zu gestalten, nutzen Sie statt eines File-Streams einen 
fest codierten String-Stream (innerhalb von `input`)
```
    std::stringstream data{string("1 3 10 2 2")};
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

End of `Tasks – Exam 2`
