#ifndef STORAGE_MANAGER_SEL_EVENT_RECORD_HPP
#define STORAGE_MANAGER_SEL_EVENT_RECORD_HPP

#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>

#include <array>

struct SelEventRecord
{
    uint16_t recordID;                //!< Record ID.
    uint8_t recordType;               //!< Record Type.
    uint32_t timeStamp;               //!< Timestamp.
    uint16_t generatorID;             //!< Generator ID.
    uint8_t eventMsgRevision;         //!< Event Message Revision.
    uint8_t sensorType;               //!< Sensor Type.
    uint8_t sensorNum;                //!< Sensor Number.
    uint8_t eventType;                //!< Event Dir | Event Type.
    std::array<uint8_t, 3> eventData; //!< Event Data
} __attribute__((packed));

#endif // STORAGE_MANAGER_SEL_EVENT_RECORD_HPP
