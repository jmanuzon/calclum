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
#include "formatcontext.h"
#include "codeccontext.h"

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
        const std::string _path{};
        std::unique_ptr<formatcontext> _pFormatContextWrapper{};
        std::unique_ptr<codeccontext> _pCodecContextWrapper{};
        int _index{-1};
};

#endif