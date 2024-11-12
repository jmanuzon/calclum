#ifndef __FORMATCONTEXT_H__
#define __FORMATCONTEXT_H__

#include <memory>
#include "ffmpeg.h"
#include "helper.h"

class formatcontext
{
public:
    formatcontext(const std::string&);
    formatcontext(const formatcontext&) = delete;
    formatcontext& operator=(const formatcontext&) = delete;

    formatcontext(formatcontext&&) = default;
    formatcontext& operator=(formatcontext&&) = default;

public:
    AVFormatContext* getPtr() const { return _pFormatContext.get(); }

private:
    std::unique_ptr<AVFormatContext, DeleterPtr<AVFormatContext, void, avformat_close_input>> _pFormatContext;
};

#endif