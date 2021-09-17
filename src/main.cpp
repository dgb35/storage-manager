#include "constants.hpp"
#include "storage_manager.hpp"

#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>

#include <iostream>

struct SELEventRecord
{
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

    manager.clearStorage();

    const SELEventRecord write{1, 2, 3, 4, 5, 6, 7, 8, {9, 10, 11}};
    {
        auto stream = manager.file_stream();
        boost::archive::binary_oarchive out_archive(
            stream, boost::archive::no_header | boost::archive::no_tracking);
        out_archive << write;
    }

    SELEventRecord read;
    {
        auto stream = manager.file_stream();
        boost::archive::binary_iarchive in_archive(
            stream, boost::archive::no_header | boost::archive::no_tracking);
        in_archive >> read;
    }

    std::cout << "SEL record:" << std::endl;
    std::cout << read.recordID << std::endl;
    std::cout << (int)read.recordType << std::endl;
    std::cout << read.timeStamp << std::endl;
    std::cout << read.generatorID << std::endl;
    std::cout << (int)read.eventMsgRevision << std::endl;
    std::cout << (int)read.sensorType << std::endl;
    std::cout << (int)read.sensorNum << std::endl;
    std::cout << (int)read.eventType << std::endl;
    std::cout << (int)read.eventData[0] << std::endl;
    std::cout << (int)read.eventData[1] << std::endl;
    std::cout << (int)read.eventData[2] << std::endl;

    std::cout << "SEL entry size: " << sizeof(SELEventRecord) << std::endl;
    std::cout << "Storage size: " << manager.storage_size() << std::endl;

    return 0;
}
