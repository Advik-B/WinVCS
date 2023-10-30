// WinAPI
#include <windows.h>
#include <iostream>
#include <fstream>
#include <string>

class File {
private:
    std::string path;
    std::fstream file;
public:
    File(std::string path) {
        this->path = path;
    }

    void open() {
        this->file.open(this->path, std::ios::in | std::ios::out | std::ios::binary);
    }

    // Write method, take in BINARY data as a parameter
    void write(char* data, std::string datastream="") {
        if (datastream != "") {
            // Open the file temporarily with the datastream (file:datastream)
            std::fstream temp_file(this->path + ":" + datastream, std::ios::in | std::ios::out | std::ios::binary);
            // Write the data to the file
            temp_file.write(data, sizeof(data));
            // Close the file
            temp_file.close();

        } else {
            this->file.write(data, sizeof(data));
        }
    }

    // Read method, takes in size of data to read as a parameter, if the size is -1, read the whole file
    template<typename T>
    T read(int size=-1, std::string datastream="") {
        if (datastream != "") {
            // Open the file temporarily with the datastream (file:datastream)
            std::fstream temp_file(this->path + ":" + datastream, std::ios::in | std::ios::out | std::ios::binary);
            // Read the data from the file
            T data;
            if (size == -1) {
                temp_file.read((char*)&data, sizeof(data));
            } else {
                temp_file.read((char*)&data, size);
            }
            // Close the file
            temp_file.close();
            // Return the data
            return data;

        } else {
            // Read the data from the file
            T data;
            if (size == -1) {
                this->file.read((char*)&data, sizeof(data));
            } else {
                this->file.read((char*)&data, size);
            }
            // Return the data
            return data;
        }
    }

    void close() {
        this->file.close();
    }

    // ~File is just close() in this case
    ~File() {
        this->close();
    }
};