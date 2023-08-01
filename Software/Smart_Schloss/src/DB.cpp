#include "DB.h"

//A constructor that sets the server address.
DB::DB(const char* serverURL) {
    this->serverURL = serverURL;
}

//A function that calls the wished query.
void DB::runQuery(QueryName query, const char* uid="") {
    // Perform the HTTP GET request to fetch data from the server
    HTTPClient http;
    String queryURL;
    switch(query)
    {
       case FETCH_BOOKING_DATA:
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
            }break;
        case INSERT_BOX_ACCESS:
            queryURL = String(serverURL) + "?user_id=123&ist_zu=1"; // Customize the URL for the specific query
            break;
        default:
            Serial.println("Invalid query.");
            return;
    }
}

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
}

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
}

//Do something with booking data.
bool DB::processBookingData(std::vector<JsonObject> data) {
    if (data.size() > 0) {
        for (JsonObject obj : data) 
        {
            BookingData bookingData=extractBookingData(obj);
            
            // Do something with the booking data, e.g., print, process, etc.
            // Print the extracted data for now
            Serial.print("UserID: "); Serial.println(bookingData.userID);
            Serial.print("Buchung_ID: "); Serial.println(bookingData.buchungID);
            Serial.print("Reservierungsdatum: "); Serial.println(bookingData.reservierungsdatum);
            Serial.print("Rueckgabedatum: "); Serial.println(bookingData.rueckgabedatum);
            Serial.print("Zustand (Buchung): "); Serial.println(bookingData.zustandBuchung);
            Serial.print("SchluesselID: "); Serial.println(bookingData.schluesselID);
            Serial.print("Zustand (Schluessel): "); Serial.println(bookingData.zustandSchluessel);
            Serial.print("Kasten_ID: "); Serial.println(bookingData.kastenID);
            Serial.println();
        }   
        return true;
    }
    else{
        Serial.println("No records found for the given RFID_UID."); 
        return false;             
    }           
}