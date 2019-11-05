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
#define NOMINMAX
#include <windows.h>
#include <limits>
#endif

#ifdef __unix__
#include <sys/types.h>
#include <dirent.h>
#endif

namespace Utils
{
enum Errors {
    RET_ERROR = -1,
    RET_SUCCESS = 0
};

/**
 * @class: parser
 * @description:
 * This class is used to extract files from
 * directory. API get_wavfiles() will return
 * all parsed Wav files in a directory path
 * passed as an argument to class constructor.
 */
class parser
{
public:
    parser(std::string dirpath);
    ~parser();
    std::vector<std::string> get_wavfiles(void);
private:
    std::vector<std::string> read_directory(const std::string& dir_name);
private:
    std::vector<std::string> m_wavfiles;
};

/**
 * @class: thread_pool
 * @description:
 * This class is used to create thread pool.
 * This class will utilize maximum threads
 * hardware concurrency can support in system.
 */
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
/**
 * @class: Encoder
 * @description:
 * This class is used to create encode Wav files
 * to corresponding MP3 using lame library.
 */
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
