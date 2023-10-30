#include <windows.h>
#include <iostream>
#include <string>

class File {
private:
    std::string path;
    HANDLE hFile;

public:
    File(std::string path) : path(path), hFile(NULL) {}

    bool open() {
        hFile = CreateFile(path.c_str(), GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
        return (hFile != INVALID_HANDLE_VALUE);
    }

    void close() {
        if (hFile != NULL) {
            CloseHandle(hFile);
            hFile = NULL;
        }
    }

    void write(char* data, size_t size, std::string datastream = "") {
        if (hFile == NULL) {
            std::cerr << "File is not open!" << std::endl;
            return;
        }

        if (datastream != "") {
            std::string alternateStream = path + ":" + datastream;
            HANDLE hStream = CreateFile(alternateStream.c_str(), GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
            if (hStream != INVALID_HANDLE_VALUE) {
                DWORD bytesWritten;
                WriteFile(hStream, data, static_cast<DWORD>(size), &bytesWritten, NULL);
                CloseHandle(hStream);
            } else {
                std::cerr << "Failed to open alternate data stream." << std::endl;
            }
        } else {
            DWORD bytesWritten;
            WriteFile(hFile, data, static_cast<DWORD>(size), &bytesWritten, NULL);
        }
    }

    template <typename T>
    T read(int size = -1, std::string datastream = "") {
        T data;
        if (hFile == NULL) {
            std::cerr << "File is not open!" << std::endl;
            return data;
        }

        HANDLE hStream;
        if (datastream != "") {
            std::string alternateStream = path + ":" + datastream;
            hStream = CreateFile(alternateStream.c_str(), GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
        } else {
            hStream = hFile;
        }

        if (hStream != INVALID_HANDLE_VALUE) {
            DWORD bytesRead;
            if (size == -1) {
                ReadFile(hStream, &data, sizeof(data), &bytesRead, NULL);
            } else {
                ReadFile(hStream, &data, static_cast<DWORD>(size), &bytesRead, NULL);
            }
            CloseHandle(hStream);
        } else {
            std::cerr << "Failed to open alternate data stream." << std::endl;
        }
        return data;
    }

    ~File() {
        close();
    }
};
