
#include <fstream>
#include "file.h"

File::File()
{

}

File::File(const std::string &path ) : m_file( path )
{
    set_data();
}

int File::set_path(const std::string& path)
{

    const std::filesystem::path old_path = m_file;
    m_file = path;
    const int retval = set_data();

    if( retval ) {
        // error here, return to old path
        m_file = old_path;
    }

    return retval;
}

std::string File::get_full_path() const
{
    return m_file.string();
}

std::string File::get_directory() const
{
    return m_file.parent_path().string();
}

std::string File::get_filename() const
{
    return m_file.filename().string();
}

std::string File::get_extension() const
{
    return m_file.extension().string();
}

int File::set_data()
{
    std::ifstream file;
    file.open( get_full_path().c_str(), std::ios_base::in | std::ios_base::binary );
    if( !file.is_open() ) {
        return 1;
        //std::cout << "not present file";
    }

    // get filesize
    file.seekg( 0, std::ios_base::end );
    const std::ifstream::pos_type file_end_pos = file.tellg();
    file.seekg( 0, std::ios::beg );

    const int file_size = static_cast<int>( file_end_pos );

    m_data.clear();
    m_data.resize( file_size );

    file.read( ( char * )&m_data[0], file_size );

    file.close();
    //std::cout << "file: " + get_full_path();
    //std::cout << " firsts bytes: " + std::to_string( m_data.at(0)) + " " + std::to_string(m_data.at(1)) << std::endl;
    return 0;
}

uint16_t File::get_file_header() const
{

    return *((uint16_t*)m_data.data());
}

const uint8_t* File::get_ptr() const
{
    return m_data.data();
}
uint8_t* File::get_ptr()
{
    return m_data.data();
}
