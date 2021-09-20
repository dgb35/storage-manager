#ifndef STORAGE_MANAGER_SEL_EVENT_RECORD_HPP
#define STORAGE_MANAGER_SEL_EVENT_RECORD_HPP

#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>

#include <array>

struct SelEventRecord
{
    // boost::serialization
    friend class boost::serialization::access;

    template <class Archive>
    void save(Archive& ar, const unsigned int version) const
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

    template <class Archive>
    void load(Archive& ar, const unsigned int version)
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
    BOOST_SERIALIZATION_SPLIT_MEMBER()

    // constructors
    SelEventRecord(){};
    SelEventRecord(uint16_t recordID, uint8_t recordType, uint32_t timeStamp,
                   uint16_t generatorID, uint8_t eventMsgRevision,
                   uint8_t sensorType, uint8_t sensorNum, uint8_t eventType,
                   std::array<uint8_t, 3> eventData) :
        recordID{recordID},
        recordType{recordType}, timeStamp{timeStamp}, generatorID{generatorID},
        eventMsgRevision{eventMsgRevision}, sensorType{sensorType},
        sensorNum{sensorNum}, eventType{eventType}, eventData{eventData}
    {}

    // fields
    uint16_t recordID;                //!< Record ID.
    uint8_t recordType;               //!< Record Type.
    uint32_t timeStamp;               //!< Timestamp.
    uint16_t generatorID;             //!< Generator ID.
    uint8_t eventMsgRevision;         //!< Event Message Revision.
    uint8_t sensorType;               //!< Sensor Type.
    uint8_t sensorNum;                //!< Sensor Number.
    uint8_t eventType;                //!< Event Dir | Event Type.
    std::array<uint8_t, 3> eventData; //!< Event Data
};

#endif // STORAGE_MANAGER_SEL_EVENT_RECORD_HPP
