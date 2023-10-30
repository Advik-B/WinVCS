#include "data_streams.cpp"
#include <windows.h>
#include "datatypes/vcs_file.cpp"
#include <bit7z/bitarchivewriter.hpp>
#include <filesystem>

bit7z::Bit7zLibrary initBit7z() {
    using namespace bit7z;
    Bit7zLibrary lib{"lib/7z.dll"};
    return lib;
}

const std::string tempdir = std::filesystem::temp_directory_path().string();

using std::string;
class CompressableFile {

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
        File* file_object;

        CompressableFile(string filepath) {
            this->filepath = filepath;
            this->properties = get_file_properties(filepath);
            this->file_object = new File(filepath);
        }

        void compress(std::string datastream) {
            // Use bit7z to compress the file
            using namespace bit7z;
            Bit7zLibrary lib = initBit7z();
            BitArchiveWriter archive{lib, BitFormat::SevenZip};
            archive.addFile(this->filepath, datastream);
            archive.compressTo(tempdir + "/temp.7z");
            // Now, use the File object to read the compressed file
            File *tempFileObject = new File(tempdir + "/temp.7z");
            tempFileObject->open();


        }
};