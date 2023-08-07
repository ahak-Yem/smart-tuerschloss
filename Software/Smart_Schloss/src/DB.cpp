#include "DB.h"

//A constructor that sets the server address.
DB::DB(const char* serverURL) {
    Serial.println("DB initialized");
    this->serverURL = serverURL;
};

void DB::runQuery(QueryName query, FetchBookingDataQuery fetchParameter) {
// Perform the HTTP GET request to fetch data from the server
    HTTPClient http;
    String queryURL;
    String uid=fetchParameter.uid;
    if(query==FETCH_BOOKING_DATA)
    {
        if(uid!=""){
            queryURL = String(serverURL) + "fetch_booking_data.php?rfid_uid="+ uid;
            http.begin(queryURL);
            int httpCode = http.GET();
            if (httpCode == HTTP_CODE_OK) {
                String payload = http.getString();
                std::vector<JsonObject> jsonObjects = deserializeJsonObj(payload);
                processBookingData(jsonObjects);
            } 
            else{
                Serial.println("HTTP GET request failed");
            }
            http.end();
        }
    }
    else{
        Serial.println("Invalid query or function is used wrong.");
        return;
    }
};

void DB::runQuery(QueryName query, InsertBoxAccessQuery insertQuery)
{   
    // Perform the HTTP GET request to fetch data from the server
    HTTPClient http;
    String queryURL;
    String userId=insertQuery.userId;
    bool isClosed=insertQuery.isClosed;
    if(query==INSERT_BOX_ACCESS)
    {//http://insert_box_access.php/?user_id=1&ist_zu=true
        if(userId != "" && userId!="0"){
            queryURL = String(serverURL) + "insert_box_access.php/?user_id=" + userId + "&ist_zu=" + (isClosed ? "true" : "false");
            http.begin(queryURL);
            int httpCode = http.GET();
            if (httpCode == HTTP_CODE_OK) {
                String payload = http.getString();
                Serial.println(payload);
            }
        }
    }
    else{
        Serial.println("Invalid query or function is used wrong.");
        return;
    }
};

void DB::runQuery(QueryName query, UpdateKeyStateQuery updateKeyQuery)
{
    if (query == UPDATE_KEY_STATE) 
    {
        updateKeyState(updateKeyQuery);
    }
};

void DB::runQuery(QueryName query, UpdateBookingStateQuery updateBookingQuery)
{
    if (query == UPDATE_BOOKING_STATE) 
    {
        updateBookingState(updateBookingQuery);
    }
}

void DB::runQuery(QueryName query, UpdateBoxDoorState updateBoxState){
    if(query == UPDATE_BoxDoor_STATE){
        updateBoxDoorState(updateBoxState);
    }
}

void DB::runQuery(QueryName query, UpdateKastenZugangState updateBoxState){
    if(query == UPDATE_DOORSTATE_KASTENZUGANG){
        updateKastenZugangState(updateBoxState);
    }
}


std::vector<BookingData> DB::getCurrentBookings()
{
    Serial.println("Getting current bookings");
    if(this->currentBookings.size() > 0){
        Serial.println("Current bookings are not empty!");
    }
    else
    {
        Serial.println("No current bookings.");
    }
    return this->currentBookings;
};

//Deserialize the JSON response and create a vector of json objects.
std::vector<JsonObject> DB::deserializeJsonObj(String payload) {
    // Calculate the required capacity dynamically based on payload size
    const size_t capacity = JSON_ARRAY_SIZE(10) + 10 * JSON_OBJECT_SIZE(8) + payload.length();
    DynamicJsonDocument doc(capacity);

    // Parse the JSON data
    DeserializationError error = deserializeJson(doc, payload);

    // Check for parsing errors
    if (error) {
        Serial.print("deserializeJson() failed: ");
        Serial.println(error.c_str());
        return std::vector<JsonObject>(); // Return an empty vector on error
    }

    // Extract the data from JSON and return it as a vector of JsonObjects
    std::vector<JsonObject> jsonObjects;
    JsonArray dataArray = doc.as<JsonArray>();
    for (JsonObject obj : dataArray) {
        jsonObjects.push_back(obj);
    }
    return jsonObjects;
};

//Extracts only BookingData from a JSON object.
BookingData DB::extractBookingData(JsonObject obj){
    BookingData bookingData;
    bookingData.userID = obj["UserID"];
    bookingData.buchungID = obj["Buchung_ID"];
    bookingData.reservierungsdatum = obj["Reservierungsdatum"];
    bookingData.rueckgabedatum = obj["Rueckgabedatum"];
    bookingData.zustandBuchung = obj["Buchung_Zustand"];
    bookingData.schluesselID = obj["SchluesselID"];
    bookingData.zustandSchluessel = obj["Schluessel_Zustand"];
    bookingData.kastenID = obj["Kasten_ID"];
    return bookingData; 
};

//Do something with booking data.
bool DB::processBookingData(std::vector<JsonObject> data) {
    if (data.size() > 0) {
        for (JsonObject obj : data) 
        {
            BookingData bookingData=extractBookingData(obj);
            this->currentBookings.push_back(bookingData);
            // // Do something with the booking data, e.g., print, process, etc.
            // // Print the extracted data for now
            // Serial.print("UserID: "); Serial.println(bookingData.userID);
            // Serial.print("Buchung_ID: "); Serial.println(bookingData.buchungID);
            // Serial.print("Reservierungsdatum: "); Serial.println(bookingData.reservierungsdatum);
            // Serial.print("Rueckgabedatum: "); Serial.println(bookingData.rueckgabedatum);
            // Serial.print("Zustand (Buchung): "); Serial.println(bookingData.zustandBuchung);
            // Serial.print("SchluesselID: "); Serial.println(bookingData.schluesselID);
            // Serial.print("Zustand (Schluessel): "); Serial.println(bookingData.zustandSchluessel);
            // Serial.print("Kasten_ID: "); Serial.println(bookingData.kastenID);
            // Serial.println();
            // delay(10000);//TODO:remove
        }   
        return true;
    }
    else{
        Serial.println("No records found for the given RFID_UID."); 
        return false;             
    }           
};

void DB::updateKeyState(UpdateKeyStateQuery updateKeyQuery)
{
   // Perform the HTTP GET request to update data in the schluessel table
    HTTPClient http;
    String queryURL;
    String schluesselID = updateKeyQuery.schluesselID;
    String schluesselZustand = keyStateToString(updateKeyQuery.schluesselZustand);

    // Check if the provided Schluessel_Zustand is one of the valid values
    if (schluesselZustand == "") {
        Serial.println("Error: Invalid value for Schluessel_Zustand. Possible values are: 'reserviert', 'verfuegbar', 'abgeholt', 'verloren'");
        return;
    }

    if (schluesselID != "" && schluesselID != "0") {
        queryURL = String(serverURL) + "update_key_state.php/?SchluesselID=" + schluesselID + "&Schluessel_Zustand=" + schluesselZustand;
        http.begin(queryURL);
        int httpCode = http.GET();
        if (httpCode == HTTP_CODE_OK) {
            String payload = http.getString();
            Serial.println(payload);
        }
    }
};

void DB::updateBookingState(UpdateBookingStateQuery updateBookingQuery)
{
    // Perform the HTTP GET request to update data in the buchung table
    HTTPClient http;
    String queryURL;
    String buchungID = updateBookingQuery.buchungID;
    String zustand = bookingZustandToString(updateBookingQuery.zustand);
    String abholungszeit = updateBookingQuery.abholungszeit;
    String abgabezeit = updateBookingQuery.abgabezeit;

    if (buchungID != "" && buchungID != "0" && updateBookingQuery.zustand >= BuchungZustandEnum::gebucht && updateBookingQuery.zustand <= BuchungZustandEnum::spaet) {
        queryURL = String(serverURL) + "update_booking_state.php/?buchungID=" + buchungID + "&zustand=" + zustand;

        if (abholungszeit != "null" && abholungszeit !="") {
            queryURL += "&abholungszeit=" + abholungszeit;
        }

        if (abgabezeit != "null" && abgabezeit !="") {
            queryURL += "&abgabezeit=" + abgabezeit;
        }
        Serial.println(queryURL);
        http.begin(queryURL);
        int httpCode = http.GET();
        if (httpCode == HTTP_CODE_OK) {
            String payload = http.getString();
            Serial.println(payload);
        }
        else
        {    
            Serial.println("The server took too long to respond!");
        }
    }
    else
        Serial.println("A parameter is wrong!");
}

void DB::updateBoxDoorState(UpdateBoxDoorState updateBoxState){
    HTTPClient http;
    String queryURL;
    String kastenID = updateBoxState.kastenID;
    String tuerZustand =(updateBoxState.tuerZustand==BoxDoorStateEnum::Zu ? "Zu" : "Auf");
    bool istBelegt = updateBoxState.istBelegt;

    // Convert boolean istBelegt to string value
    String istBelegtValue = (istBelegt ? "ja" : "nein");

    queryURL = String(serverURL) + "update_box_door_state.php?kastenID=" + kastenID + "&tuerZustand=" + tuerZustand + "&istBelegt=" + istBelegtValue;

    http.begin(queryURL);
    int httpCode = http.GET();
    if (httpCode == HTTP_CODE_OK) {
        String payload = http.getString();
        Serial.println(payload);
    } else {
        Serial.println("HTTP GET request failed");
    }
    http.end();
}

void DB::updateKastenZugangState(UpdateKastenZugangState updateKastenState){
    HTTPClient http;
    String queryURL;
    String ID = updateKastenState.ID;
    bool IstZu = updateKastenState.IstZu;

    queryURL = String(serverURL) + "update_doorstate_kastenzugang.php?ID=" + ID + "&IstZu=" + IstZu;

    Serial.println(queryURL);
    http.begin(queryURL);
    int httpCode = http.GET();
    if (httpCode == HTTP_CODE_OK) {
        String payload = http.getString();
        Serial.println(payload);
    } else {
        Serial.println("HTTP GET request failed");
    }
    http.end();
};

String DB::keyStateToString(KeyStateEnum::KeyState state) {
    switch (state) {
        case KeyStateEnum::reserviert:
            return "reserviert";
        case KeyStateEnum::verfuegbar:
            return "verfuegbar";
        case KeyStateEnum::abgeholt:
            return "abgeholt";
        case KeyStateEnum::verloren:
            return "verloren";
        default:
            return "";
    }
}
void DB::clearCurrentBookings(){
    this->currentBookings.empty();
};

String DB::bookingZustandToString(BuchungZustandEnum::BuchungZustand zustand) {
    switch (zustand) {
        case BuchungZustandEnum::gebucht:
            return "gebucht";
        case BuchungZustandEnum::abgeholt:
            return "abgeholt";
        case BuchungZustandEnum::zurueckgegeben:
            return "zurueckgegeben";
        case BuchungZustandEnum::storniert:
            return "storniert";
        case BuchungZustandEnum::abgesagt:
            return "abgesagt";
        case BuchungZustandEnum::abgelaufen:
            return "abgelaufen";
        case BuchungZustandEnum::spaet:
            return "spaet";
        default:
            return "";
    }
};
