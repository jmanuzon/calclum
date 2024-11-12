#include <stdexcept>
#include "codeccontext.h"

codeccontext::codeccontext(const AVCodec* pCodec, const AVCodecParameters* pCodecParameters)
{
    _pCodecContext = std::unique_ptr<AVCodecContext, DeleterPtr<AVCodecContext, void, avcodec_free_context>>
    { avcodec_alloc_context3(pCodec) };

    auto ptr = _pCodecContext.get();

    if (!ptr)
    {
        throw std::invalid_argument("avcodec_alloc_context3 failed.");
    }

    if (avcodec_parameters_to_context(ptr, pCodecParameters) < 0)
    {
        throw std::invalid_argument("avcodec_parameters_to_context failed.");
    }

    if (avcodec_open2(ptr, pCodec, NULL) < 0)
    {
        throw std::invalid_argument("avcodec_open2 failed.");
    }
}