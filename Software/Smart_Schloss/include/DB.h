#ifndef DB_h
#define DB_h

#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <Arduino.h>
#include <vector>

//All possible queries.
enum QueryName {
    NOTHING,
    FETCH_BOOKING_DATA,
    INSERT_BOX_ACCESS,
    UPDATE_BOOKING_STATE,
    UPDATE_BoxDoor_STATE,
    UPDATE_DOORSTATE_KASTENZUGANG,
    UPDATE_KEY_STATE
};

//All possible box door states.
namespace BoxDoorStateEnum{
    enum BoxDoorState{
        Auf,
        Zu
    };
}

//All possible key states.
namespace KeyStateEnum {
    enum KeyState {
        reserviert, 
        verfuegbar, 
        abgeholt, 
        verloren
    };
}

//All possible booking states.
namespace BuchungZustandEnum {
    enum BuchungZustand {
        gebucht,
        abgeholt,
        zurueckgegeben,
        storniert,
        abgesagt,
        abgelaufen,
        spaet
    };
}

//Struct for booking data response.
struct BookingData {
    char* userID;
    char* buchungID;
    char* reservierungsdatum;
    char* rueckgabedatum;
    char* zustandBuchung;
    char* schluesselID;
    char* zustandSchluessel;
    char* kastenID;
};

//Struct to hold parameters for the UpdateKeyState query.
struct UpdateKeyStateQuery{
    char* schluesselID;
    KeyStateEnum::KeyState schluesselZustand;
};

//Struct to hold parameters for the FetchBookingData query.
struct FetchBookingDataQuery {
    String uid;
};

//Struct to hold parameters for the InsertBoxAccess query.
struct InsertBoxAccessQuery {
    char* userId;
    bool isClosed;
};

//Struct to hold parameters for the UpdateBookingState query.
struct UpdateBookingStateQuery {
    String buchungID;
    BuchungZustandEnum::BuchungZustand zustand;
    String abholungszeit;
    String abgabezeit;
};

//Struct to hold parameters for the UpdateBoxState query.
struct UpdateBoxDoorState{
    const char* kastenID;
    BoxDoorStateEnum::BoxDoorState tuerZustand;
    bool istBelegt;
};

//Struct to hold parameters for the UpdateKastenZugangState query.
struct UpdateKastenZugangState {
    char* ID;
    bool IstZu;
};

class DB {
public:
    DB(const char* serverURL);
    void runQuery(QueryName query, FetchBookingDataQuery fetchParameter);
    void runQuery(QueryName query, InsertBoxAccessQuery insertQuery);
    void runQuery(QueryName query, UpdateKeyStateQuery updateKeyQuery);
    void runQuery(QueryName query, UpdateBookingStateQuery updateBookingQuery);
    void runQuery(QueryName query, UpdateBoxDoorState updateBoxState);
    void runQuery(QueryName query, UpdateKastenZugangState updateBoxState);
    std::vector<BookingData> getCurrentBookings();
    static String bookingZustandToString(BuchungZustandEnum::BuchungZustand zustand);
private:
    std::vector<BookingData> currentBookings;
    const char* serverURL;
    std::vector<JsonObject> deserializeJsonObj(String payload);
    BookingData extractBookingData(JsonObject data);
    bool processBookingData(std::vector<JsonObject> data);
    void updateKeyState(UpdateKeyStateQuery updateKeyQuery);
    void updateBookingState(UpdateBookingStateQuery updateBookingQuery);
    void updateBoxDoorState(UpdateBoxDoorState updateBoxState);
    void updateKastenZugangState(UpdateKastenZugangState updateKastenState);
    String keyStateToString(KeyStateEnum::KeyState state);
};

#endif