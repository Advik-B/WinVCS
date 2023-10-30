#include <string>

struct Attributes {
    bool ReadOnly;
    bool Hidden;
    // Advanced
    bool FileIsReadyForArchiving;
    bool FileContentIndexing;
    bool FileCompressed;
    bool FileEncrypted;
};

struct TimeStamp {
    int Year;
    int Month;
    int Day;
    int Hour;
    int Minute;
    int Second;
};

struct FileProperties {
    std::string TypeOfFile;
    float FileSize;
    float FileSizeOnDisk;
    TimeStamp FileCreated;
    TimeStamp FileModified;
    TimeStamp FileAccessed;
    Attributes FileAttributes;

};