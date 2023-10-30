#include "data_streams.cpp"
#include <windows.h>
#include "datatypes/vcs_file.cpp"

using std::string;
class VCS_File {

    private:
        // Use windows API to get file properties
        static FileProperties get_file_properties(string filepath) {
            FileProperties properties;
            WIN32_FILE_ATTRIBUTE_DATA file_attributes;
            GetFileAttributesEx(filepath.c_str(), GetFileExInfoStandard, &file_attributes);
            properties.FileAttributes.ReadOnly = file_attributes.dwFileAttributes & FILE_ATTRIBUTE_READONLY;
            properties.FileAttributes.Hidden = file_attributes.dwFileAttributes & FILE_ATTRIBUTE_HIDDEN;
            properties.FileAttributes.FileIsReadyForArchiving = file_attributes.dwFileAttributes & FILE_ATTRIBUTE_ARCHIVE;
            properties.FileAttributes.FileContentIndexing = file_attributes.dwFileAttributes & FILE_ATTRIBUTE_NOT_CONTENT_INDEXED;
            properties.FileAttributes.FileCompressed = file_attributes.dwFileAttributes & FILE_ATTRIBUTE_COMPRESSED;
            properties.FileAttributes.FileEncrypted = file_attributes.dwFileAttributes & FILE_ATTRIBUTE_ENCRYPTED;
            properties.FileSize = file_attributes.nFileSizeLow;
            properties.FileSizeOnDisk = file_attributes.nFileSizeHigh;
            properties.FileCreated.Year = file_attributes.ftCreationTime.dwHighDateTime;
            properties.FileCreated.Month = file_attributes.ftCreationTime.dwLowDateTime;
            properties.FileModified.Year = file_attributes.ftLastWriteTime.dwHighDateTime;
            properties.FileModified.Month = file_attributes.ftLastWriteTime.dwLowDateTime;
            properties.FileAccessed.Year = file_attributes.ftLastAccessTime.dwHighDateTime;
            properties.FileAccessed.Month = file_attributes.ftLastAccessTime.dwLowDateTime;
            return properties;
        }
    public:
        string filepath;
        FileProperties properties;
        VCS_File(const string& filepath) {
            this->filepath = filepath;
            this->properties = get_file_properties(filepath);
        }


};