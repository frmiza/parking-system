#ifndef FILEHANDLER_HPP
#define FILEHANDLER_HPP

#include <iostream>
#include <fstream>
#include <cstring>
#include <iomanip>

namespace FH
{
    class FileHandler
    {
    private:
        char* buffer;
        std::size_t size_file;

    public:
        FileHandler();
        ~FileHandler();
        void read_file(const std::string& file_name);
        void save_file(const std::string& file_name, char* buffer_to_save);
    
    //Gets
        char* get_buffer() const;
        std::size_t get_size() const;
    };
}

#endif // FILEHANDLER_HPP