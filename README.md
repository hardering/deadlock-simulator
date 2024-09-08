# Deadlock-Simulator

Dieses Projekt wurde im Rahmen des Moduls **Betriebssysteme** an der Hochschule-Ruhr-West im Fachbereich Angewandte Informatik erstellt.

## Vorwort

Ein C/C++-basierter Deadlock-Simulator mit einer grafischen Benutzeroberfläche zur Visualisierung und Bewertung von Algorithmen zur Erkennung, Verhinderung und Auflösung von Deadlocks.

Der Fokus liegt auf der Kernfunktionalität des Simulators, der verschiedene Deadlock-Szenarien erzeugt und es ermöglicht, unterschiedliche Strategien zur Deadlockerkennung, -vermeidung und -behebung zu testen. Hierbei werden unter anderem der Banker's Algorithmus sowie Strategien zur Ressourcenprävention, Prozessunterbrechung und -rücksetzung unterstützt. Die implementierte API stellt sicher, dass diese Algorithmen in der Simulationsumgebung wiederholt und unter verschiedenen Bedingungen evaluiert werden können. Ein grafisches Interface visualisiert eine Tabelle, welche die Zustände der Prozesse und Ressourcen während der Ausführung der verschiedenen Strategien demonstriert.

## Projekt aufsetzen

### Voraussetzungen

Dieses Projekt erfordert:
- CMake (zum Kompilieren des Projekts)
- Das Qt Framework in der Version `6.5.1` (zur Erstellung der grafischen Benutzeroberfläche)

### Qt Setup

Für dieses Projekt wird das Qt-Framework benötigt, das vor der Kompilierung installiert sein muss. Der Installationspfad für Qt muss während der CMake-Konfiguration bereitgestellt werden.

### Für MacOS:

```bash
cmake -DCMAKE_PREFIX_PATH="~/Qt/6.5.1/macos" .
```

### Für Linux:

```bash
cmake -DCMAKE_PREFIX_PATH="~/Qt/6.5.1/gcc_64" .
```

### Kompilieren des Projekts

Nachdem Qt installiert und der Installationspfad in der CMake-Konfiguration festgelegt wurde, können Sie das Projekt wie folgt kompilieren:
**Wichtig**: `CMake 3.29` wurde festgelegt und wird hier spezifisch benötigt.
1. Navigieren Sie in der CMD zum Projektordner.
2. Führen Sie die folgendenen Befehle aus:

```bash
mkdir build && cd build
cmake ..
make
```

Nach erfolgreicher Kompilierung finden Sie die ausführbare Datei im Ordner `build`.

## Bedienung des Simulators

1. Starten Sie das Programm. Daraufhin öffnet sich das GUI.
2. Wählen Sie eine der folgenden Optionen, um die Deadlock-Algorithmen zu testen:

- **Generate Deadlock**: Erzeugt eine Deadlock-Situation mit mehreren Prozessen und Ressourcen.
- **Run Banker's Algorithm**: Führt den Banker's Algorithmus durch, um zu prüfen, ob das System in einem sicheren Zustand ist.
- **Run Interrupt Process**: Unterbricht einen Prozess, um Deadlocks aufzulösen.
- **Run Abort Process**: Bricht einen Prozess ab, um Deadlocks aufzulösen.
- **Reset**: Setzt die Simulation zurück.

## Struktur des Codes

Das Projekt ist in verschiedene Komponenten unterteilt, die jeweils unterschiedliche Aspekte der Deadlock-Simulation und -Verwaltung übernehmen. Hier ist eine Übersicht der wichtigsten Dateien und Klassen:

### 1. `main.cpp`

Die Hauptfunktion der Anwendung. Hier wird die grafische Benutzeroberfläche erstellt und die verschiedenen Deadlock-Algorithmen und Strategien aufgerufen.

### 2. `Window.h` und `Window.cpp`

Verantwortlich für das Hauptfenster der grafischen Benutzeroberfläche. Hier werden die Interaktionselemente (wie Buttons) und die Tabellen, die die Zustände der Prozesse und Ressourcen anzeigen, definiert und verwaltet.

### 3. `Process.h` und `Process.cpp`

Diese Dateien definieren die `Process`-Klasse. Ein `Process` repräsentiert einen laufenden Prozess in der Simulation und speichert Informationen wie die maximale Ressourcennutzung, die zugeteilten Ressourcen und die Priorität des Prozesses. Die Klasse enthält Methoden zum Anfordern und Freigeben von Ressourcen.

```cpp
class Process {
public:
    Process(int id, const std::vector<int>& maxRes, int prio);
    bool requestResources(const std::vector<int>& request, std::vector<Resource>& resources);
    void releaseResources(std::vector<Resource>& resources);
};
```

### 4. `Resource.h` und `Resource.cpp`

Definiert die `Resource`-Klasse, die die verfügbaren Ressourcen im System repräsentiert. Sie enthält Methoden zur Zuteilung und Freigabe von Ressourcen.

### 5. `Deadlock.h`, `Deadlock.cpp`, `DeadlockRecovery.h` und `DeadlockRecovery.cpp`

Diese Dateien enthalten die Algorithmen zur Deadlockerkennung und -lösung. Der `DeadlockRecovery`-Klasse bietet verschiedene Strategien zur Lösung von Deadlocks, wie Unterbrechung eines Prozesses oder Rücksetzen auf einen früheren Zustand.

```cpp
class DeadlockRecovery {
public:
    bool detectDeadlock(const std::vector<Process>& processes, const std::vector<Resource>& resources);
    void resolveDeadlock(std::vector<Process>& processes, std::vector<Resource>& resources, const std::string& strategy);
};
```

### 6. `BankersAlgorithm.h` und `BankersAlgorithm.cpp`

Der Banker's Algorithmus wird hier implementiert, um zu überprüfen, ob eine angeforderte Ressourcenzuteilung sicher ist oder nicht. Diese Klasse ist für die Überprüfung des sicheren Zustands des Systems zuständig.

### 7. Tests

Die Tests für den Banker's Algorithmus und die Deadlock-Strategien werden in den Dateien `BankersAlgorithmTest.h` und `DeadlockTest.h` definiert.

```cpp
class BankersAlgorithmTest {
public:
    void runAllTests();
};
```

## Mitgewirkte Personen

- Tim Wittlerbäumer
- Daria Hardering
