#ifndef __VIDEO_H__
#define __VIDEO_H__
#pragma once
#include <string>
#include <memory>
#include <functional>
#include <vector>

#include "ffmpeg.h"
#include "helper.h"
#include "frame.h"

class video
{
    public:
        video(const std::string&);
        video(const video& other) = default;
        video& operator=(const video&) = default;

        video(video&&) = default;
        video& operator=(video&&) = default;

    public:
        std::vector<frame> getFrames() const;

    private:
         std::unique_ptr<AVFormatContext, DeleterPtr<AVFormatContext, void, avformat_close_input>> _pFormatContext;
         std::unique_ptr<AVCodecContext, DeleterPtr<AVCodecContext, void, avcodec_free_context>> _pCodecContext;
         int _index{-1};
};

#endif