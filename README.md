# Fachübergereifendes Projekt
### Smart Türschloss

* Teammitglieder:
  -Firas Ben Yedder 
  -Nader Gongi
  -Heltonn Harold
  -Ahmed Kutbi 

* Team: **03**
* Semester: **05**

## Projektziel : 
* Das Ziel dieses Projekts ist die Entwicklung eines Smartes Schlosses und eines Buchungssystems für den Urban Garden an der Hochschule für Technik und Wirtschaft Berlin (HTW). Das intelligente Schloss dient der sicheren  Aufbewahrung des Schlüssels für den Zugang zum Urban Garden und ermöglicht nur autorisierten Personen den Zugang. Das Buchungssystem ermöglicht den Nutzern die einfache Überprüfung der Werkzeugverfügbarkeit und die Buchung von Ressourcen. Durch die Implementierung dieses Tool-Management-Systems streben wir an, die Effizienz und Transparenz bei der Nutzung der Ressourcen im Urban Garden zu verbessern und zukünftige studentische Initiativen zu unterstützen.

* Funktionalitäten : 

  -Implementierung eines sicheren Schließsystems zur Zugangskontrolle
 
  -Benutzerfreundliches Buchungssystem zur Überprüfung von Werkzeugverfügbarkeit und Buchung von Ressourcen

  -Verbesserung der Ordnung, Sicherheit und Effizienz im Urban Garden


## Voraussetzungen
 
* Um das Projekt erfolgreich zu installieren, benötigen Sie die folgenden Tools und Komponenten:

  + Visual Studio Code (https://code.visualstudio.com/)
  + PlatformIO-Erweiterung für Visual Studio Code
  + Freenove ESP32 Wrover-Dev Board (oder ein ähnliches ESP32-Board)
  + USB-Kabel zum Anschließen des ESP32 an den Computer

## Installationsschritte
### 1 Projekt klonen: 
Klonen Sie das Projekt entweder über SSH oder HTTPS von GitLab:

#### SSH:
```
git clone git@gitlab.rz.htw-berlin.de:fachpro-23/03-smart-tuerschloss.git
```

#### HTTPS:
```
git clone https://gitlab.rz.htw-berlin.de/fachpro-23/03-smart-tuerschloss.git.

```

### 2 Projektordner auswählen:

 Navigieren Sie zum heruntergeladenen Projektordner und wählen Sie ihn aus, um ihn zu öffnen.

### 3 PlatformIO konfigurieren:

Öffnen Sie die PlatformIO-Konfiguration, indem Sie auf das PlatformIO-Symbol in der linken Seitenleiste klicken und dann auf "pick a folder " klicken.

### 4 Bibliotheken installieren:

 Öffnen Sie die PlatformIO Library Manager, indem Sie auf das PlatformIO-Symbol in der linken Seitenleiste klicken und dann auf "Libraries" (Bibliotheken) klicken. 
Suchen Sie nach den Bibliotheken und installieren : 
 + "Arduino" 
 + "MFRC522" 
 + "SPI" 

  Externe Bibliothek "quirc.h" einbinden: Laden Sie die externe Bibliothek "quirc.h" von folgender URL herunter: https://github.com/dlbeer/quirc. Entpacken Sie das heruntergeladene Archiv und kopieren Sie den Ordner "quirc" in das Verzeichnis "lib" im Projektordner.

### Code einführen : 
* Verbindung herstellen: Verbinden Sie den ESP32 über das USB-Kabel mit Ihrem Computer. Stellen Sie sicher, dass der richtige Port in der PlatformIO-Konfiguration ausgewählt ist, um die Verbindung herzustellen.

  Code kompilieren und hochladen: Klicken Sie auf das PlatformIO-Symbol in der linken Seitenleiste und wählen Sie "Upload" (Hochladen), um den Code auf den ESP32 zu kompilieren und hochzuladen. Überprüfen Sie die Ausgabe in der Konsole, um sicherzustellen, dass der Vorgang erfolgreich abgeschlossen wurde.

## Links,Hinweise 
  0. https://code.visualstudio.com/docs 
  1. https://docs.platformio.org/en/latest/ 
  2. https://randomnerdtutorials.com/getting-started-freenove-esp32-wrover-cam/

