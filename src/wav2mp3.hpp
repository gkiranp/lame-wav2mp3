#ifndef _WAV2MP3_HEADER_
#define _WAV2MP3_HEADER_
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <thread>
#include <cassert>
#include <functional>
#include "lame.h"

#ifdef _WIN32
#include <windows.h>
#endif

#ifdef __unix__
#include <sys/types.h>
#include <dirent.h>
#endif

#define DEBUG 1

namespace Utils
{
enum Errors {
    RET_ERROR = -1,
    RET_SUCCESS = 0
};

void Usage(void);

class parser
{
public:
    parser(std::string dirpath);
    ~parser();
    std::vector<std::string> get_wavfiles(void);
    void Usage(void);
private:
    std::vector<std::string> read_directory(const std::string& dir_name);
private:
    std::vector<std::string> m_wavfiles;
};

class thread_pool
{
public:
    thread_pool(const std::vector<std::string> &wavfiles);
    ~thread_pool();
    void run(void);
    void finish(void);
private:
    std::vector<std::thread> m_Pool;
    std::vector<std::string> m_wavfiles;
};

} //end-of-namespace-Utils

namespace Application
{

class Encoder
{
public:
    Encoder(Utils::thread_pool *tpool);
    ~Encoder();
    void encode_wav2mp3(void);
    
private:
    Utils::thread_pool *m_Tpool;
};

} //end-of-namespace-Application


#endif //_WAV2MP3_HEADER_
