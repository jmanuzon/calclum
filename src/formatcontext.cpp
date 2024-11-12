#include <stdexcept>
#include "formatcontext.h"

formatcontext::formatcontext(const std::string& path)
{
    _pFormatContext = std::unique_ptr<AVFormatContext, DeleterPtr<AVFormatContext, void, avformat_close_input>>
    { avformat_alloc_context() };

    auto ptr = _pFormatContext.get();

    if(ptr == nullptr)
    {
        throw std::invalid_argument("avformat_alloc_context failed.");
    }

    if(avformat_open_input(&ptr, path.c_str(), NULL, NULL) != 0)
    {
        throw std::invalid_argument("avformat_open_input failed.");
    }

    if (avformat_find_stream_info(ptr,  NULL) < 0) 
    {
        throw std::invalid_argument("avformat_find_stream_info failed.");
    }
}