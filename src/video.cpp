#include "video.h"
#include "frame.h"

#include <stdexcept>
#include <iostream>

video::video(const std::string& path)
{
    _pFormatContext = std::unique_ptr<AVFormatContext, DeleterPtr<AVFormatContext, void, avformat_close_input>>
    { avformat_alloc_context() };

    if(!_pFormatContext)
    {
        throw std::invalid_argument("avformat_close_input failed.");
    }

    auto ptr = _pFormatContext.get();

    if(avformat_open_input(&ptr, path.c_str(), NULL, NULL) != 0)
    {
        throw std::invalid_argument("avformat_open_input failed.");
    }

    if (avformat_find_stream_info(_pFormatContext.get(),  NULL) < 0) 
    {
        throw std::invalid_argument("avformat_find_stream_info failed.");
    }

    const AVCodec *pCodec{};
    AVCodecParameters *pCodecParameters{};

    for (unsigned int i = 0; i < _pFormatContext->nb_streams; i++)
    {
        AVCodecParameters *pLocalCodecParameters = _pFormatContext->streams[i]->codecpar;
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

    _pCodecContext = std::unique_ptr<AVCodecContext, DeleterPtr<AVCodecContext, void, avcodec_free_context>>
     { avcodec_alloc_context3(pCodec) };

    if (!_pCodecContext)
    {
          throw std::invalid_argument("avcodec_alloc_context3 failed.");
    }

    if (avcodec_parameters_to_context(_pCodecContext.get(), pCodecParameters) < 0)
    {
        throw std::invalid_argument("avcodec_parameters_to_context failed.");
    }

    if (avcodec_open2(_pCodecContext.get(), pCodec, NULL) < 0)
    {
        throw std::invalid_argument("avcodec_open2 failed.");
    }
}

std::vector<frame> video::getFrames() const
{
    std::vector<frame> frames{};

    auto pPacket = std::unique_ptr<AVPacket, DeleterPtr<AVPacket, void, av_packet_free>>{av_packet_alloc()};

    if (!pPacket)
    {
        throw std::runtime_error("av_packet_alloc failed"); 
    }

    while (av_read_frame(_pFormatContext.get(), pPacket.get()) >= 0)
    {
        if (pPacket->stream_index == _index) {  

            auto result = avcodec_send_packet(_pCodecContext.get(), pPacket.get());
            
            if(result < 0)
                continue;

            while (result >= 0)
            {
                frame pFrame;

                result = avcodec_receive_frame(_pCodecContext.get(), pFrame.get());

                if (result == AVERROR(EAGAIN) || result == AVERROR_EOF) 
                {
                    break;
                }
                else if(result < 0)
                {
                    continue;
                }

                if (pFrame.get()->format == AV_PIX_FMT_YUV420P)
                {
                   frames.push_back(std::move(pFrame));
                }
                else
                {
                    std::cout << "Format: " << pFrame.get()->format; 
                }
            }
        }

        av_packet_unref(pPacket.get());
    } 

    return frames;
}