#include "FileHandler.hpp"

FH::FileHandler::FileHandler() :
    buffer(nullptr),
    size_file(0) {}

FH::FileHandler::~FileHandler()
{
    delete[] buffer;
}

void FH::FileHandler::read_file(const std::string& file_name)
{
    std::ifstream file(file_name, std::ios::binary | std::ios::ate);
    if(!file){
        file.close();
        exit(EXIT_FAILURE);
    }

    // Obtem tamanho e retorna o ponteiro para inicio
    size_file = file.tellg();
    file.seekg(0, std::ios::beg);

    buffer = new char[size_file];

    if(!file.read(buffer,size_file)){
        delete[] buffer;
        buffer = nullptr;
        size_file = 0;
        file.close();
        exit(EXIT_FAILURE);
    }
    else
        file.close();
}

void FH::FileHandler::save_file(const std::string& file_name, char* buffer_to_save)
{
    std::ofstream file(file_name);
    if (file.is_open()) {
        file << std::setw(4) << buffer_to_save;
        file.close();
    }
}

char* FH::FileHandler::get_buffer() const 
{
    return buffer;
}

std::size_t FH::FileHandler::get_size() const
{
    return size_file;
}