#include "constants.hpp"
#include "storage_manager.hpp"

#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>

#include <iostream>

struct SELEventRecord
{
    friend class boost::serialization::access;

    template <class Archive>
    void serialize(Archive& ar, const unsigned int version)
    {
        ar& recordID;
        ar& recordType;
        ar& timeStamp;
        ar& generatorID;
        ar& eventMsgRevision;
        ar& sensorType;
        ar& sensorNum;
        ar& eventType;
        ar& eventData[0];
        ar& eventData[1];
        ar& eventData[2];
    }

    uint16_t recordID;                //!< Record ID.
    uint8_t recordType;               //!< Record Type.
    uint32_t timeStamp;               //!< Timestamp.
    uint16_t generatorID;             //!< Generator ID.
    uint8_t eventMsgRevision;         //!< Event Message Revision.
    uint8_t sensorType;               //!< Sensor Type.
    uint8_t sensorNum;                //!< Sensor Number.
    uint8_t eventType;                //!< Event Dir | Event Type.
    std::array<uint8_t, 3> eventData; //!< Event Data

    SELEventRecord(){};
    SELEventRecord(uint16_t recordID, uint8_t recordType, uint32_t timeStamp,
                   uint16_t generatorID, uint8_t eventMsgRevision,
                   uint8_t sensorType, uint8_t sensorNum, uint8_t eventType,
                   std::array<uint8_t, 3> eventData) :
        recordID{recordID},
        recordType{recordType}, timeStamp{timeStamp}, generatorID{generatorID},
        eventMsgRevision{eventMsgRevision}, sensorType{sensorType},
        sensorNum{sensorNum}, eventType{eventType}, eventData{eventData}
    {}
};

int main()
{
    StorageManager manager(dir / file_name);
    std::cout << "Path to file: " << dir << std::endl;

    const SELEventRecord selEventRecord{1, 1, 1, 1, 1, 1, 1, 1, {1, 2, 3}};

    auto stream = manager.getFileStream();

    {
        boost::archive::text_oarchive out_archive(stream);
        out_archive << selEventRecord;
    }

    return 0;
}
