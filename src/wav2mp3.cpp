#include "wav2mp3.hpp"

namespace Application 
{
//lambda-fun to get MP3 file extension from Wav file
auto get_mp3_ext = [](const std::string &wav) {
    std::string mp3str = wav;
    return mp3str.replace(mp3str.length()-3, 3, "mp3");
};
    
//lambda-func to convert Wav to MP3
std::function<void(std::string)> encode = [](const std::string &fwav)
{
    //convert wav to mp3
    const int WAV_SIZE = 8192;
    const int MP3_SIZE = 8192;
    int read, write;
    std::string fmp3 = get_mp3_ext(fwav);
    FILE *wav = fopen(fwav.c_str(), "rb");
    FILE *mp3 = fopen(fmp3.c_str(), "wb");

    short int wav_buf[WAV_SIZE*2];
    unsigned char mp3_buf[MP3_SIZE];

    lame_t lame = lame_init();
    lame_set_in_samplerate(lame, 44100);
    lame_set_VBR(lame, vbr_default);
    lame_init_params(lame);

    do {
        read = fread(wav_buf, 2*sizeof(short int), WAV_SIZE, wav);
        if (read == 0)
            write = lame_encode_flush(lame, mp3_buf, MP3_SIZE);
        else
            write = lame_encode_buffer_interleaved(lame, wav_buf, read, mp3_buf, MP3_SIZE);
        fwrite(mp3_buf, write, 1, mp3);
    } while (read != 0);

    lame_close(lame);
    fclose(mp3);
    fclose(wav);
};

} //end-of-namespace-Application

Utils::parser::parser(std::string dirpath)
{
    try {
        m_wavfiles = read_directory(dirpath);
    }
    catch(const std::exception& e) {
        std::cout << "Error reading from " << dirpath << ": " << e.what() << '\n';
        Usage();
    }
}	
	
void Utils::parser::Usage(void)
{
    std::cout << "None";
}
	
std::vector<std::string> Utils::parser::read_directory(const std::string& dir_name)
{
    std::vector<std::string> wavfiles;
    if(!dir_name.empty()) 
    {
        //lambda-fun to get file extension
        auto get_file_ext = [](const std::string &fname) {
            size_t i = fname.rfind('.', fname.length());
            std::string ext = (i != std::string::npos)? (fname.substr(i+1, fname.length()-i)):(""); 
            return ext;
        };
        //lambda-fun to convert string to lowercase
        auto str_to_lower = [](std::string str) {
            std::for_each(str.begin(), str.end(), [](char & c){c = ::tolower(c);}); return str;
        };
        //temp-string
        std::string fname = "";
#ifdef __unix__
        DIR* dirp = opendir(dir_name.c_str());
        struct dirent * dp;
        while ((dp = readdir(dirp)) != NULL) {
            if(str_to_lower(get_file_ext(dp->d_name)) == "wav") {
                fname = dir_name + "/" + dp->d_name;
                wavfiles.push_back(fname);
            }
        }
        closedir(dirp);
#endif
#ifdef _WIN32
    std::string fp(dir_name);
    fp.append("\\*");
    WIN32_FIND_DATA fdata;
    HANDLE hFind = INVALID_HANDLE_VALUE;
    if ((hFind = FindFirstFile(fp.c_str(), &fdata)) != INVALID_HANDLE_VALUE) 
    {
        do {
            if(str_to_lower(get_file_ext(fdata.cFileName)) == "wav") {
                fname = dir_name + "\\" + fdata.cFileName;
                wavfiles.push_back(fname);
            }
        } while (FindNextFile(hFind, &fdata) != 0);
        FindClose(hFind);
    }
#endif
    }
    return wavfiles;
}

Utils::parser::~parser()
{
}

std::vector<std::string> Utils::parser::get_wavfiles(void)
{
    return m_wavfiles;
}

Utils::thread_pool::thread_pool(const std::vector<std::string> &wavfiles) : m_wavfiles(wavfiles)
{
    assert(!m_wavfiles.empty());
}

Utils::thread_pool::~thread_pool()
{
    m_Pool.clear();
}

void Utils::thread_pool::run(void)
{
    //Lets create a thread-pools to convert files
    const int no_of_threads = std::min(static_cast<int>(m_wavfiles.size()), static_cast<int>(std::thread::hardware_concurrency()));
    for(int i = 0; i < no_of_threads; ++i)
    {
#ifdef DEBUG
        std::cout << "File " << m_wavfiles[i] << " is being encoded to MP3" << std::endl;
#endif
        m_Pool.push_back(std::thread(Application::encode, std::ref(m_wavfiles[i])));
    }
}

void Utils::thread_pool::finish(void)
{
    for(std::thread& th: m_Pool)
    {
        if(th.joinable())
            th.join();
    }
}

Application::Encoder::Encoder(Utils::thread_pool *tpool): m_Tpool(tpool)
{
    assert(m_Tpool != nullptr);
}

Application::Encoder::~Encoder()
{
}

void Application::Encoder::encode_wav2mp3(void)
{
    assert(m_Tpool != nullptr);
    //call the thread pool to execute
    m_Tpool->run();
    m_Tpool->finish();
}

int main(int argc, char** argv)
{
    if(argc < 2) {
        //Utils::parser::Usage();
        return Utils::Errors::RET_ERROR;
    }
    const std::string dir_path(argv[1]);
    Utils::parser p(dir_path);
    std::vector<std::string> wavfiles = p.get_wavfiles();
    
#ifdef DEBUG
    for(auto &a: wavfiles)
        std::cout << a << std::endl;
#endif
    if(!wavfiles.empty()) 
    {
        //Convertion using thread-pool
        Utils::thread_pool tpool(wavfiles);
        Application::Encoder en(&tpool);
        en.encode_wav2mp3();
    }
    return Utils::Errors::RET_SUCCESS;
}
