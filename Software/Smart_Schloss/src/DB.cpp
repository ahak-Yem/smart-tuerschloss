#include "DB.h"

//A constructor that sets the server address.
DB::DB(const char* serverURL) {
    Serial.println("DB initialized");
    this->serverURL = serverURL;
}

DB::~DB(){
};

void DB::runQuery(QueryName query, FetchBookingDataQuery fetchParameter) {
    // Perform the HTTP POST request to fetch data from the server
    HTTPClient http;
    http.setTimeout(30000); // Set timeout to 30 seconds
    http.clearAllCookies();
    
    String queryURL;
    String uid = fetchParameter.uid;

    if (query == FETCH_BOOKING_DATA) {
        if (uid != "") {
            queryURL = String(serverURL) + "key_availability/";

            // Create the POST data JSON object
            DynamicJsonDocument postDataJson(128);
            postDataJson["rfid_uid"] = uid;

            // Serialize the JSON object to a string
            String postData;
            serializeJson(postDataJson, postData);

            // Start the HTTP client
            http.begin(queryURL);
            http.addHeader("Content-Type", "application/json");
            http.addHeader("Accept", "*/*");
            http.addHeader("Accept-Encoding", "gzip, deflate, br");

            int httpCode = http.POST(postData);

            if (httpCode == HTTP_CODE_OK) {
                String payload = http.getString();
                std::vector<JsonObject> jsonObjects = deserializeJsonObj(payload);
                processBookingData(jsonObjects);
            } else {
                Serial.println("HTTP POST request failed");
            }
            http.end();
        }
    } else {
        Serial.println("Invalid query or function is used wrong.");
        return;
    }
}

void DB::runQuery(QueryName query, InsertBoxAccessQuery insertQuery)
{   
    // Perform the HTTP GET request to fetch data from the server
    HTTPClient http;
    http.setTimeout(30000); // Set timeout to 10 seconds
    http.clearAllCookies();

    String queryURL;
    String userId=insertQuery.userId;
    bool isClosed=insertQuery.isClosed;

    if(query==INSERT_BOX_ACCESS)
    {
        String queryURL = String(serverURL) + "insert_box_access/";
        if(userId != "" && userId!="0"){

            // Create the POST data JSON object
            StaticJsonDocument<256> requestBody;
            requestBody["user_id"] = userId;
            requestBody["ist_zu"] = isClosed;

            // Serialize the JSON body
            String requestBodyStr;
            serializeJson(requestBody, requestBodyStr);

            http.begin(queryURL);
            http.addHeader("Content-Type", "application/json");
            http.addHeader("Accept", "*/*");
            http.addHeader("Accept-Encoding", "gzip, deflate, br");

            int httpCode = http.POST(requestBodyStr);
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
    if(this->currentBookings.size() > 0){
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
    const size_t capacity = JSON_OBJECT_SIZE(1) + JSON_ARRAY_SIZE(10) + 10 * JSON_OBJECT_SIZE(9) + payload.length();
    DynamicJsonDocument doc(capacity);

    DeserializationError error = deserializeJson(doc, payload);

    if (error) {
        Serial.print("deserializeJson() failed: ");
        Serial.println(error.c_str());
        return std::vector<JsonObject>();
    }

    // Extract the data from JSON and return it as a vector of JsonObjects

    std::vector<JsonObject> jsonObjects;
    JsonObject root = doc.as<JsonObject>();
    
    // Iterate through the numeric keys and extract the JSON objects
    for (JsonPair keyValue : root) {
        if (keyValue.value().is<JsonObject>()) {
            jsonObjects.push_back(keyValue.value().as<JsonObject>());
        }
    }
    
    return jsonObjects;
}

//Extracts only BookingData from a JSON object.
BookingData DB::extractBookingData(JsonObject obj){
    BookingData bookingData;
    bookingData.userID = obj["UserID"];
    bookingData.buchungID = obj["Buchung_ID"];
    String correctedReservierungsdatum = this->correctDrupalTimestamp(obj["Reservierungsdatum"]);
    bookingData.reservierungsdatum = strdup(correctedReservierungsdatum.c_str());

    String correctedRueckgabedatum = this->correctDrupalTimestamp(obj["Rueckgabedatum"]);
    bookingData.rueckgabedatum = strdup(correctedRueckgabedatum.c_str());

    bookingData.zustandBuchung = obj["Buchung_Zustand"];
    bookingData.schluesselID = obj["SchluesselID"];
    bookingData.zustandSchluessel = obj["Schluessel_Zustand"];
    bookingData.kastenID = obj["KastenID"];
    bookingData.Kasten_Node_ID = obj["Kasten_Node_ID"];
    
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
    http.clearAllCookies();
    http.setTimeout(30000);
    String queryURL = String(serverURL) + "update_key_state";
    
    String schluesselID = updateKeyQuery.schluesselID;
    String schluesselZustand = keyStateToString(updateKeyQuery.schluesselZustand);

    // Check if the provided Schluessel_Zustand is one of the valid values
    if (schluesselZustand == "") {
        Serial.println("Error: Invalid value for Schluessel_Zustand. Possible values are: 'reserviert', 'verfuegbar', 'abgeholt', 'verloren'");
        return;
    }
    if (schluesselID != "" && schluesselID != "0") {
        http.addHeader("Content-Type", "application/json");
        http.addHeader("Accept", "*/*");
        http.addHeader("Accept-Encoding", "gzip, deflate, br");

        StaticJsonDocument<256> requestBody;
        requestBody["SchluesselID"] = schluesselID;
        requestBody["Schluessel_Zustand"]=schluesselZustand;

        // Serialize the JSON body
        String requestBodyStr;
        serializeJson(requestBody, requestBodyStr);

        http.begin(queryURL);
        int httpCode = http.POST(requestBodyStr);
        if (httpCode == HTTP_CODE_OK) {
            String payload = http.getString();
            Serial.println(payload);
        }
    }
};

//TODO(Need to be fixed with Julien)
void DB::updateBookingState(UpdateBookingStateQuery updateBookingQuery)
{
    /// Perform the HTTP GET request to update data in the buchung table
    HTTPClient http;
    http.setTimeout(30000);
    http.clearAllCookies();

    String queryURL = String(serverURL) + "update_booking_state";

    String buchungID = updateBookingQuery.buchungID;
    String zustand = bookingZustandToString(updateBookingQuery.zustand);
    String abholungszeit = updateBookingQuery.abholungszeit;
    String abgabezeit = updateBookingQuery.abgabezeit;

    http.addHeader("Content-Type", "application/json");
    http.addHeader("Accept", "*/*");
    http.addHeader("Accept-Encoding", "gzip, deflate, br");


    if (buchungID != "" && buchungID != "0" && updateBookingQuery.zustand >= BuchungZustandEnum::gebucht && updateBookingQuery.zustand <= BuchungZustandEnum::spaet) {
        StaticJsonDocument<256> requestBody;
        requestBody["buchungID"] = buchungID;
        requestBody["zustand"]=zustand;
        if (abholungszeit != "null" && abholungszeit !="") {
            requestBody["abholungszeit"]=abholungszeit;
        }
        if (abgabezeit != "null" && abgabezeit !="") {
            requestBody["abgabezeit"]=abgabezeit;
        }

        // Serialize the JSON body
        String requestBodyStr;
        serializeJson(requestBody, requestBodyStr);

        http.begin(queryURL);
        int httpCode = http.POST(requestBodyStr);
        if (httpCode == HTTP_CODE_OK) {
            String payload = http.getString();
            Serial.println(payload);
            http.end();
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
    http.clearAllCookies();
    http.setTimeout(30000);

    String queryURL = String(serverURL) + "update_door_state_box/";

    if (updateBoxState.kastenID != "" ) {
        //Construct the JSON request body
        StaticJsonDocument<256> requestBody;
        requestBody["node_id"] = updateBoxState.kastenID;
        requestBody["istBelegt"] = updateBoxState.istBelegt;
        requestBody["tuerZustand"] = updateBoxState.tuerZustand;

        // Start the HTTP client
        http.begin(queryURL);
        http.addHeader("Content-Type", "application/json");
        http.addHeader("Accept", "*/*");
        http.addHeader("Accept-Encoding", "gzip, deflate, br");

        // Serialize the JSON body
        String requestBodyStr;
        serializeJson(requestBody, requestBodyStr);

        int httpCode = http.POST(requestBodyStr);
        if (httpCode == HTTP_CODE_OK) {
            String payload = http.getString();
            http.end();
            Serial.println(payload);
        } else {
            Serial.println("HTTP POST request failed");
        }
    }
}

void DB::updateKastenZugangState(UpdateKastenZugangState updateKastenState){
    HTTPClient http;
    http.clearAllCookies();
    http.setTimeout(30000);


    String queryURL=String(serverURL) + "update_doorstate_kastenzugang/";
    
    String ID = updateKastenState.ID;
    bool IstZu = updateKastenState.IstZu;
    if(ID!="" && !ID.isEmpty()){

        http.addHeader("Content-Type", "application/json");
        http.addHeader("Accept", "*/*");
        http.addHeader("Accept-Encoding", "gzip, deflate, br");
        
        //Construct the JSON request body
        StaticJsonDocument<256> requestBody;
        requestBody["ID"] = ID;
        requestBody["IstZu"] = IstZu;

        // Serialize the JSON body
        String requestBodyStr;
        serializeJson(requestBody, requestBodyStr);

        http.begin(queryURL);
        int httpCode = http.POST(requestBodyStr);
        if (httpCode == HTTP_CODE_OK) {
            String payload = http.getString();
            Serial.println(payload);
        } else {
            Serial.println("HTTP GET request failed");
        }
        http.end();
    }
}

String DB::urlEncode(String value)
{
    String encodedValue = "";
    char c;
    for (size_t i = 0; i < value.length(); i++) {
        c = value.charAt(i);
        if (isAlphaNumeric(c)) {
            encodedValue += c;
        } else if (c == ' ') {
            encodedValue += "+";
        } else {
            encodedValue += String('%') + String(c, HEX);
        }
    }
    return encodedValue;
}

String DB::correctDrupalTimestamp(const char *timestamp)
{
    String correctedTimestamp = timestamp;
    int position = correctedTimestamp.indexOf('T'); // Find the position of 'T'

    if (position != -1) {
        correctedTimestamp[position] = ' '; // Replace 'T' with space
    }
    return correctedTimestamp;
};

String DB::keyStateToString(KeyStateEnum::KeyState state) {
    switch (state) {
        case KeyStateEnum::reserviert:
            return "Reserviert";
        case KeyStateEnum::verfuegbar:
            return "Verfuegbar";
        case KeyStateEnum::abgeholt:
            return "Abgeholt";
        case KeyStateEnum::verloren:
            return "Verloren";
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
            return "Gebucht";
        case BuchungZustandEnum::abgeholt:
            return "Abgeholt";
        case BuchungZustandEnum::zurueckgegeben:
            return "Zurueckgegeben";
        case BuchungZustandEnum::storniert:
            return "Storniert";
        case BuchungZustandEnum::abgesagt:
            return "Abgesagt";
        case BuchungZustandEnum::abgelaufen:
            return "Abgelaufen";
        case BuchungZustandEnum::spaet:
            return "Spaet";
        default:
            return "";
    }
};

