# deadlock-simulator

Dieses Projekt wurde im Rahmen des Moduls **Betriebssysteme** an der Hochschule-Ruhr-West im Fachbereich Angewandter
Informatik erstellt.

## Vorwort

Ein C/C++-basierter Deadlock-Simulator mit einer grafischen Benutzeroberfläche zur Visualisierung und Bewertung von  
Algorithmen zur Erkennung, Verhinderung, und Auflösen von Deadlocks.

Der Fokus liegt auf der Kernfunktionalität des Simulators, der verschiedene Deadlock-Szenarien erzeugt und es erlaubt,
unterschiedliche Strategien zur Deadlockerkennung, -vermeidung und -behebung zu testen. Hierbei werden unter anderem der
Banker's Algorithmus sowie Strategien zur Ressourcenprävention, Prozessunterbrechung und -rücksetzung unterstützt. Die
implementierte API stellt sicher, dass diese Algorithmen in der Simulationsumgebung wiederholt und unter verschiedenen
Bedingungen evaluiert werden können. Ein grafisches Interface visualisiert eine Tabelle, welche die Zustände der
Prozesse und Ressourcen während der Ausführung der verschiedenen Strategien demonstriert.

## Projekt aufsetzen

Für dieses Projekt benötigt es das Framework Qt mit der Version ``6.5.1``, welches auf dem Gerät installiert sein muss.
Anschließend benötigt das Projekt für die erfolgreiche Kompilierung noch den Installationspfad.

Für MacOS:

``cmake -DCMAKE_PREFIX_PATH="~/Qt/6.5.1/macos" .``

## Benutzte Technologien

- C/C++

- Qt-Framework zur Erstellung der graphischen Benutzeroberfläche

## Mitgewirkte Personen

Tim Wittlerbäumer

Daria Hardering
