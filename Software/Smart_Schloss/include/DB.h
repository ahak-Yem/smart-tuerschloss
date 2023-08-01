#ifndef DB_h
#define DB_h

#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <Arduino.h>
#include <vector>

//Struct for booking data response.
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

//Struct to hold parameters for the FetchBookingData query
struct FetchBookingDataQuery {
    const char* uid;
};

//Struct to hold parameters for the InsertBoxAccess query
struct InsertBoxAccessQuery {
    const char* userId;
    bool isClosed;
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
    void runQuery(QueryName query, FetchBookingDataQuery fetchParameter);
    void runQuery(QueryName query, InsertBoxAccessQuery insertQuery);
private:
    const char* serverURL;
    std::vector<JsonObject> deserializeJsonObj(String payload);
    BookingData extractBookingData(JsonObject data);
    bool processBookingData(std::vector<JsonObject> data);
};

#endif
