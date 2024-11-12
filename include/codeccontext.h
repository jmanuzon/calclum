#ifndef __CODECCONTEXT_H__
#define __CODECCONTEXT_H__

#include <memory>
#include "ffmpeg.h"
#include "helper.h"

class codeccontext
{
public:
    codeccontext(const AVCodec*, const AVCodecParameters*);
    codeccontext(const codeccontext&) = delete;
    codeccontext& operator=(const codeccontext&) = delete;

    codeccontext(codeccontext&&) = default;
    codeccontext& operator=(codeccontext&&) = default;

public:
    AVCodecContext* getPtr() const { return _pCodecContext.get(); }

private:
    std::unique_ptr<AVCodecContext, DeleterPtr<AVCodecContext, void, avcodec_free_context>> _pCodecContext;
};

#endif