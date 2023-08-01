#ifndef DB_h
#define DB_h

#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <Arduino.h>

//A struct for booking data only.
struct BookingData {
    const char* userID;
    const char* buchungID;
    const char* reservierungsdatum;
    const char* rueckgabedatum;
    const char* zustandBuchung;
    const char* schluesselID;
    const char* zustandSchluessel;
    const char* kastenID;
};

//All possible queries.
enum QueryName {
    NOTHING,
    FETCH_BOOKING_DATA,
    INSERT_BOX_ACCESS
};

class DB {
public:
    DB(const char* serverURL);
    void runQuery(QueryName query, const char* uid);
    const char* serverURL;

private:
    // const char* serverURL;
    std::vector<JsonObject> deserializeJsonObj(String payload);
    BookingData extractBookingData(JsonObject data);
    bool processBookingData(std::vector<JsonObject> data);
};

#endif