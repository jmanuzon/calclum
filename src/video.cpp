#include "video.h"
#include "frame.h"
#include "packet.h"

#include <stdexcept>
#include <iostream>

video::video(const std::string& path) : _path(path)
{
    _pFormatContextWrapper = std::make_unique<formatcontext>(path);
    auto pFormatContext = _pFormatContextWrapper->getPtr();

    const AVCodec *pCodec{};
    AVCodecParameters *pCodecParameters{};

    for (unsigned int i = 0; i < pFormatContext->nb_streams; i++)
    {
        AVCodecParameters *pLocalCodecParameters = pFormatContext->streams[i]->codecpar;
        const AVCodec *pLocalCodec = avcodec_find_decoder(pLocalCodecParameters->codec_id);

         if (pLocalCodec== nullptr)
         {
            continue;
         }

         //only handle video
         if (pLocalCodecParameters->codec_type == AVMEDIA_TYPE_VIDEO)
         {
            if(_index == -1)
            {
                _index = i;
                pCodec = pLocalCodec;
                pCodecParameters = pLocalCodecParameters;
            }
         }
         else
         {
            continue;
         }
    }

    if (_index == -1) 
    {
        throw std::invalid_argument("not a video stream.");
    }     

    _pCodecContextWrapper = std::make_unique<codeccontext>(pCodec, pCodecParameters);
}

std::vector<frame> video::getFrames() const
{
    std::vector<frame> frames{};

    packet packet;

    auto pPacket = packet.getPtr();
    auto pFormatContext = _pFormatContextWrapper->getPtr();
    auto pCodecContext = _pCodecContextWrapper->getPtr();

    while (av_read_frame(pFormatContext, pPacket) >= 0)
    {
        if (pPacket->stream_index == _index) {  

            auto result = avcodec_send_packet(pCodecContext, pPacket);
            
            if(result < 0)
                continue;

            while (result >= 0)
            {
                frame frame;
                auto pFrame = frame.getPtr();

                result = avcodec_receive_frame(pCodecContext, pFrame);

                if (result == AVERROR(EAGAIN) || result == AVERROR_EOF) 
                {
                    break;
                }
                else if(result < 0)
                {
                    continue;
                }

                if (pFrame->format == AV_PIX_FMT_YUV420P)
                {
                   frames.push_back(std::move(frame));
                }
                else
                {
                    std::cout << "Format: " << pFrame->format; 
                }
            }
        }

        packet.unref();
    } 

    return frames;
}