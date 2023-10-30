#include <windows.h>
#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>

class FilePermissionException : public std::runtime_error {
public:
    FilePermissionException(const std::string& message) : std::runtime_error(message) {}
};

class FileADSException : public std::runtime_error {
public:
    FileADSException(const std::string& message) : std::runtime_error(message) {}
};

class FileReadException : public std::runtime_error {
public:
    FileReadException(const std::string& message) : std::runtime_error(message) {}
};

class FileNotOpenException : public std::runtime_error {
public:
    FileNotOpenException(const std::string& message) : std::runtime_error(message) {}
};

class File {
private:
    std::string path;
    HANDLE hFile;

public:
    File(std::string path) : path(path), hFile(NULL) {}

    bool open() {
        hFile = CreateFile(path.c_str(), GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
        if (hFile == INVALID_HANDLE_VALUE) {
            throw FilePermissionException("Failed to open the file due to permissions.");
        }
        return true;
    }

    void close() {
        if (hFile != NULL) {
            CloseHandle(hFile);
            hFile = NULL;
        }
    }

    void write(char* data, size_t size, std::string datastream = "") {
        if (hFile == NULL) {
            throw FileNotOpenException("File is not open!");
        }

        if (datastream != "") {
            std::string alternateStream = path + ":" + datastream;
            HANDLE hStream = CreateFile(alternateStream.c_str(), GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
            if (hStream != INVALID_HANDLE_VALUE) {
                DWORD bytesWritten;
                if (!WriteFile(hStream, data, static_cast<DWORD>(size), &bytesWritten, NULL)) {
                    throw FileADSException("Failed to write to alternate data stream.");
                }
                CloseHandle(hStream);
            } else {
                throw FileADSException("Failed to open alternate data stream.");
            }
        } else {
            DWORD bytesWritten;
            if (!WriteFile(hFile, data, static_cast<DWORD>(size), &bytesWritten, NULL)) {
                throw FilePermissionException("Failed to write to the file.");
            }
        }
    }

    template <typename T>
    T read(int size = -1, std::string datastream = "") {
        T data;
        if (hFile == NULL) {
            throw FileNotOpenException("File is not open!");
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
                if (!ReadFile(hStream, &data, sizeof(data), &bytesRead, NULL)) {
                    throw FileReadException("Failed to read from alternate data stream.");
                }
            } else {
                if (!ReadFile(hStream, &data, static_cast<DWORD>(size), &bytesRead, NULL)) {
                    throw FileReadException("Failed to read from alternate data stream.");
                }
            }
            CloseHandle(hStream);
        } else {
            throw FileADSException("Failed to open alternate data stream.");
        }
        return data;
    }

    ~File() {
        close();
    }
};
