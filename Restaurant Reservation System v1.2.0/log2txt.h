#ifndef LOG_2_TXT_H
#define LOG_2_TXT_H

#include <fstream>
#include <string>

class log2txt
{
private:
    std::string filename;
    std::ofstream file;

public:
    log2txt(const std::string& filename);

    ~log2txt();

    void log(const std::string& message);

    void log_n(const std::string& message);

};

#endif
