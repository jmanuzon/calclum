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
         std::shared_ptr<AVFormatContext> _pFormatContext;
         std::shared_ptr<AVCodecContext> _pCodecContext;
         int _index{-1};
};

#endif