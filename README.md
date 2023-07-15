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
* Das Ziel dieses Projekts ist die Entwicklung eines Smartes Schlosses und eines Buchungssystems für den Urban Garden an der Hochschule für Technik und Wirtschaft Berlin (HTW). Das intelligente Schloss dient der sicheren  Aufbewahrung des Schlüssels für den Zugang zum Urban Garden und ermöglicht nur autorisierten Personen den Zugang. Das Buchungssystem ermöglicht den Nutzern die einfache Überprüfung der Schlüsselverfügbarkeit und die Buchung von Ressourcen. Durch die Implementierung dieses Systems streben wir an, die Effizienz und Transparenz bei der Nutzung der Ressourcen im Urban Garden zu verbessern und zukünftige studentische Initiativen zu unterstützen.

* Funktionalitäten : 

  -Implementierung eines sicheren Schließsystems zur Zugangskontrolle
 
  -Benutzerfreundliches Buchungssystem zur Überprüfung von Schlüsselverfügbarkeit und Buchung von Ressourcen

  -Verbesserung der Ordnung, Sicherheit und Effizienz im Urban Garden


## Voraussetzungen
 
* Um das Projekt erfolgreich zu installieren, benötigen Sie die folgenden Tools und Komponenten:

  + Visual Studio Code (https://code.visualstudio.com/)
  + PlatformIO-Erweiterung für Visual Studio Code
  + Freenove ESP32 Wrover-Dev Board (oder ein ähnliches ESP32-Board)
  + USB-Kabel zum Anschließen des ESP32 an den Computer

# Installationsschritte 

## Teil 1  : Installation von Docker Engine 

### 1 Aktualisieren Sie den apt-Paketindex und installieren Sie die erforderlichen Pakete, um apt die Verwendung eines Repositorys über HTTPS zu ermöglichen : 
```
sudo apt-get update
sudo apt-get install ca-certificates curl gnupg
``` 
### 2 Fügen Sie den offiziellen GPG-Schlüssel von Docker hinzu:
```
sudo install -m 0755 -d /etc/apt/keyrings
curl -fsSL https://download.docker.com/linux/ubuntu/gpg | sudo gpg --dearmor -o /etc/apt/keyrings/docker.gpg
sudo chmod a+r /etc/apt/keyrings/docker.gpg
``` 
### 3 Richten Sie das Docker-Repository ein, indem Sie eine Repository-Datei erstellen:
```
echo "deb [arch=$(dpkg --print-architecture) signed-by=/etc/apt/keyrings/docker.gpg] https://download.docker.com/linux/ubuntu $(. /etc/os-release && echo "$VERSION_CODENAME") stable" | sudo tee /etc/apt/sources.list.d/docker.list > /dev/null
```
### 4 Aktualisieren Sie erneut den apt-Paketindex:

```
sudo apt-get update 

```
### 5 Installieren Sie Docker Engine, containerd und Docker Compose: 
```
sudo apt-get install docker-ce docker-ce-cli containerd.io docker-compose
``` 
### 6 Überprüfen Sie die erfolgreiche Installation von Docker Engine, indem Sie das hello-world-Image ausführen:
```
sudo docker run hello-world

``` 


# Teil 2  : Drupal-Schnitstelle 


### 1 klonen Sie das Repository von GitHub mit dem folgenden Befehl:
```
   git clone git@github.com:MethodJules/xnavi_d9.git
```
### 2 Wechseln Sie in den key_management-Branch mit dem folgenden Befehl: 
```
cd xnavi_d9
git checkout key_management
```
### 3 Navigieren Sie zum docker-Verzeichnis des Projekts:
```
cd docker
``` 
### 4 Führen Sie den folgenden Befehl aus, um die Docker-Container zu starten: 
```
sudo docker-compose up -d

``` 
### 5 Laden Sie den Datenbankdump von folgender URL herunter: xnavi_key_management_dump.sql. Speichern Sie die Datei in das docker-Verzeichnis. 

`https://www.dropbox.com/scl/fi/qm8xofclt7sqoag50xefn/xnavi_key_management_dump.sql?dl=0&rlkey=ueayibf2w3pvy8m9wyiy9s7a4 `

### 6 Führen Sie den folgenden Befehl aus, um den Datenbankdump in die MySQL-Datenbank einzulesen: 
```
sudo docker exec -i xnavi_d9_mariadb mysql -uroot -pxnavi_d9 xnavi_d9 < xnavi_key_management_dump.sql
``` 
### 7 Nachdem der Datenbankdump erfolgreich eingelesen wurde, sollte das xnavi_d9-Projekt bereit sein. Sie können auf die Website über Ihren Webbrowser zugreifen, indem Sie die URL :```   http://localhost:8080  ```



### Teil 2: Software für den Mikrocontroller
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
  3. Offizielle Drupal-Website: https://www.drupal.org/ 
  4. https://docs.docker.com/engine/install/ubuntu/ 
  5. https://github.com/MethodJules/xnavi_d9/

