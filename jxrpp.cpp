//
// Copyright (c) 2012 Mateusz Loskot <mateusz at loskot dot net>
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
#include "jxrpp.hpp"

#include <cassert>
#include <cstddef>
#include <string>

#ifdef JXRCXX_IMPLEMENTATION_WIC_ENABLED
#include <wincodec.h>
#include <wincodecsdk.h>
#include <atlbase.h>
#pragma comment(lib, "WindowsCodecs.lib")
#endif

namespace jxrpp
{

namespace detail
{

class decoder_base
{
public:
    virtual ~decoder_base() {}
    virtual void attach(char const* const filename) = 0;
    virtual std::size_t get_frame_count() const = 0;
    virtual frame_info get_frame_info(std::size_t const index) const = 0;
    virtual void read_frame(std::size_t const index, roi_info const& roi, frame_buffer& buffer) const = 0;
};

#ifdef JXRCXX_IMPLEMENTATION_REF_ENABLED

class decoder_reference : public decoder_base
{
public:
    decoder_reference()
    {
    }

    ~decoder_reference()
    {
    }

    void attach(char const* const filename)
    {
    }

    std::size_t get_frame_count() const
    {
        std::size_t frame_count(0);
        return static_cast<std::size_t>(frame_count);
    }

    frame_info get_frame_info(std::size_t const index) const
    {
        frame_info info;
        return info;
    }

    void read_frame(std::size_t const index, roi_info const& roi, frame_buffer& buffer) const
    {
    }

private:
    
};

#endif // JXRCXX_IMPLEMENTATION_REF_ENABLED

#ifdef JXRCXX_IMPLEMENTATION_WIC_ENABLED

pixel_info::tag make_pixel_format_tag(GUID const& wic_pixel_format)
{
#define JXRCXX_FORMAT(guid, pixel_format_tag) \
    else if (IsEqualGUID(wic_pixel_format, guid)) { return pixel_info::##pixel_format_tag ; }

    if (false)
    {}
    JXRCXX_FORMAT(GUID_WICPixelFormatUndefined, undefined)
    JXRCXX_FORMAT(GUID_WICPixelFormatDontCare, dontcare)
    JXRCXX_FORMAT(GUID_WICPixelFormatBlackWhite, blackwhite)
    JXRCXX_FORMAT(GUID_WICPixelFormat1bppIndexed, bpp1_indexed)
    JXRCXX_FORMAT(GUID_WICPixelFormat2bppGray, bpp2_gray)
    JXRCXX_FORMAT(GUID_WICPixelFormat2bppIndexed, bpp2_indexed)
    JXRCXX_FORMAT(GUID_WICPixelFormat4bppGray, bpp4_gray)
    JXRCXX_FORMAT(GUID_WICPixelFormat4bppIndexed, bpp4_indexed)
    JXRCXX_FORMAT(GUID_WICPixelFormat8bppAlpha, bpp8_alpha)
    JXRCXX_FORMAT(GUID_WICPixelFormat8bppGray, bpp8_gray)
    JXRCXX_FORMAT(GUID_WICPixelFormat8bppIndexed, bpp8_indexed)
    JXRCXX_FORMAT(GUID_WICPixelFormat16bppBGR555, bpp16_bgr555)
    JXRCXX_FORMAT(GUID_WICPixelFormat16bppBGR565, bpp16_bgr565)
    JXRCXX_FORMAT(GUID_WICPixelFormat16bppBGRA5551, bpp16_bgra5551)
    JXRCXX_FORMAT(GUID_WICPixelFormat16bppGray, bpp16_gray)
    JXRCXX_FORMAT(GUID_WICPixelFormat16bppGrayFixedPoint, bpp16_gray_fixedpoint)
    JXRCXX_FORMAT(GUID_WICPixelFormat16bppGrayHalf, bpp16_gray_half)
    JXRCXX_FORMAT(GUID_WICPixelFormat24bppBGR, bpp24_bgr)
    JXRCXX_FORMAT(GUID_WICPixelFormat24bpp3Channels, bpp24_channels3)
    JXRCXX_FORMAT(GUID_WICPixelFormat24bppRGB, bpp24_rgb)
    JXRCXX_FORMAT(GUID_WICPixelFormat32bppBGR, bpp32_bgr)
    JXRCXX_FORMAT(GUID_WICPixelFormat32bppBGR101010, bpp32_bgr101010)
    JXRCXX_FORMAT(GUID_WICPixelFormat32bppBGRA, bpp32_bgra)
    JXRCXX_FORMAT(GUID_WICPixelFormat32bpp3ChannelsAlpha, bpp32_channels3_alpha)
    JXRCXX_FORMAT(GUID_WICPixelFormat32bpp4Channels, bpp32_channels4)
    JXRCXX_FORMAT(GUID_WICPixelFormat32bppCMYK, bpp32_cmyk)
    JXRCXX_FORMAT(GUID_WICPixelFormat32bppGrayFixedPoint, bpp32_gray_fixedpoint)
    JXRCXX_FORMAT(GUID_WICPixelFormat32bppGrayFloat, bpp32_gray_float)
    JXRCXX_FORMAT(GUID_WICPixelFormat32bppPBGRA, bpp32_pbgra)
    JXRCXX_FORMAT(GUID_WICPixelFormat32bppPRGBA, bpp32_prgba)
    JXRCXX_FORMAT(GUID_WICPixelFormat32bppRGBA, bpp32_rgba)
    JXRCXX_FORMAT(GUID_WICPixelFormat32bppRGBA1010102, bpp32_rgba1010102)
    JXRCXX_FORMAT(GUID_WICPixelFormat32bppRGBA1010102XR, bpp32_rgba1010102_xr)
    JXRCXX_FORMAT(GUID_WICPixelFormat32bppRGBE, bpp32_rgbe)
    JXRCXX_FORMAT(GUID_WICPixelFormat40bpp4ChannelsAlpha, bpp40_channels4_alpha)
    JXRCXX_FORMAT(GUID_WICPixelFormat40bpp5Channels, bpp40_channels5)
    JXRCXX_FORMAT(GUID_WICPixelFormat40bppCMYKAlpha, bpp40_cmyk_alpha)
    JXRCXX_FORMAT(GUID_WICPixelFormat48bppBGR, bpp48_bgr)
    JXRCXX_FORMAT(GUID_WICPixelFormat48bppBGRFixedPoint, bpp48_bgr_fixedpoint)
    JXRCXX_FORMAT(GUID_WICPixelFormat48bpp3Channels, bpp48_channels3)
    JXRCXX_FORMAT(GUID_WICPixelFormat48bpp5ChannelsAlpha, bpp48_channels5_alpha)
    JXRCXX_FORMAT(GUID_WICPixelFormat48bpp6Channels, bpp48_channels6)
    JXRCXX_FORMAT(GUID_WICPixelFormat48bppRGB, bpp48_rgb)
    JXRCXX_FORMAT(GUID_WICPixelFormat48bppRGBFixedPoint, bpp48_rgb_fixedpoint)
    JXRCXX_FORMAT(GUID_WICPixelFormat48bppRGBHalf, bpp48_rgb_half)
    JXRCXX_FORMAT(GUID_WICPixelFormat56bpp6ChannelsAlpha, bpp56_channels6_alpha)
    JXRCXX_FORMAT(GUID_WICPixelFormat56bpp7Channels, bpp56_channels7)
    JXRCXX_FORMAT(GUID_WICPixelFormat64bppBGRA, bpp64_bgra)
    JXRCXX_FORMAT(GUID_WICPixelFormat64bppBGRAFixedPoint, bpp64_bgra_fixedpoint)
    JXRCXX_FORMAT(GUID_WICPixelFormat64bpp3ChannelsAlpha, bpp64_channels3_alpha)
    JXRCXX_FORMAT(GUID_WICPixelFormat64bpp4Channels, bpp64_channels4)
    JXRCXX_FORMAT(GUID_WICPixelFormat64bpp7ChannelsAlpha, bpp64_channels7_alpha)
    JXRCXX_FORMAT(GUID_WICPixelFormat64bpp8Channels, bpp64_channels8)
    JXRCXX_FORMAT(GUID_WICPixelFormat64bppCMYK, bpp64_cmyk)
    JXRCXX_FORMAT(GUID_WICPixelFormat64bppPBGRA, bpp64_pbgra)
    JXRCXX_FORMAT(GUID_WICPixelFormat64bppPRGBA, bpp64_prgba)
    JXRCXX_FORMAT(GUID_WICPixelFormat64bppRGBFixedPoint, bpp64_rgb_fixedpoint)
    JXRCXX_FORMAT(GUID_WICPixelFormat64bppRGBHalf, bpp64_rgb_half)
    JXRCXX_FORMAT(GUID_WICPixelFormat64bppRGBA, bpp64_rgba)
    JXRCXX_FORMAT(GUID_WICPixelFormat64bppRGBAFixedPoint, bpp64_rgba_fixedpoint)
    JXRCXX_FORMAT(GUID_WICPixelFormat64bppRGBAHalf, bpp64_rgba_half)
    JXRCXX_FORMAT(GUID_WICPixelFormat72bpp8ChannelsAlpha, bpp72_channels8_alpha)
    JXRCXX_FORMAT(GUID_WICPixelFormat80bpp4ChannelsAlpha, bpp80_channels4_alpha)
    JXRCXX_FORMAT(GUID_WICPixelFormat80bpp5Channels, bpp80_channels5)
    JXRCXX_FORMAT(GUID_WICPixelFormat80bppCMYKAlpha, bpp80_cmyk_alpha)
    JXRCXX_FORMAT(GUID_WICPixelFormat96bpp5ChannelsAlpha, bpp96_channels5_alpha)
    JXRCXX_FORMAT(GUID_WICPixelFormat96bpp6Channels, bpp96_channels6)
    JXRCXX_FORMAT(GUID_WICPixelFormat96bppRGBFixedPoint, bpp96_rgb_fixedpoint)
    JXRCXX_FORMAT(GUID_WICPixelFormat112bpp6ChannelsAlpha, bpp112_channels6_alpha)
    JXRCXX_FORMAT(GUID_WICPixelFormat112bpp7Channels, bpp112_channels7)
    JXRCXX_FORMAT(GUID_WICPixelFormat128bpp7ChannelsAlpha, bpp128_channels7_alpha)
    JXRCXX_FORMAT(GUID_WICPixelFormat128bpp8Channels, bpp128_channels8)
    JXRCXX_FORMAT(GUID_WICPixelFormat128bppPRGBAFloat, bpp128_prgba_float)
    JXRCXX_FORMAT(GUID_WICPixelFormat128bppRGBFixedPoint, bpp128_rgb_fixedpoint)
    JXRCXX_FORMAT(GUID_WICPixelFormat128bppRGBFloat, bpp128_rgb_float)
    JXRCXX_FORMAT(GUID_WICPixelFormat128bppRGBAFixedPoint, bpp128_rgba_fixedpoint)
    JXRCXX_FORMAT(GUID_WICPixelFormat128bppRGBAFloat, bpp128_rgba_float)
    JXRCXX_FORMAT(GUID_WICPixelFormat144bpp8ChannelsAlpha, bpp144_channels8_alpha)
    else
    {
        return pixel_info::undefined;
    }
}

class decoder_wic : public decoder_base
{
public:
    decoder_wic()
    {
        HRESULT hr = CoInitialize(0);
        verify(hr);
        //E_OUTOFMEMORY 
    }

    ~decoder_wic()
    {
        release();
        CoUninitialize();
    }

    void attach(char const* const filename)
    {
        HRESULT hr(S_OK);

        hr = bitmap_decoder_.CoCreateInstance(CLSID_WICWmpDecoder);
        verify(hr);

        hr = factory_.CoCreateInstance(CLSID_WICImagingFactory);
        verify(hr);

        hr = factory_->CreateStream(&stream_);
        verify(hr);

        std::wstring const wfilename(make_unicode(filename));
        hr = stream_->InitializeFromFilename(wfilename.c_str(), GENERIC_READ);
        verify(hr);

        hr = bitmap_decoder_->Initialize(stream_, WICDecodeMetadataCacheOnDemand);
        verify(hr);
    }

    std::size_t get_frame_count() const
    {
        UINT frame_count(0);
        HRESULT hr = bitmap_decoder_->GetFrameCount(&frame_count);
        verify(hr);

        assert(frame_count > 0);
        return static_cast<std::size_t>(frame_count);
    }

    frame_info get_frame_info(std::size_t const index) const
    {
        assert(index < get_frame_count());

        CComPtr<IWICBitmapFrameDecode> wic_frame;
        HRESULT hr = bitmap_decoder_->GetFrame(index, &wic_frame);
        verify(hr);

        UINT width(0);
        UINT height(0);
        hr = wic_frame->GetSize(&width, &height);
        verify(hr);
        assert(width > 0);
        assert(height > 0);

        double dpi_x(0);
        double dpi_y(0);
        hr = wic_frame->GetResolution(&dpi_x, &dpi_y);
        verify(hr);
        assert(dpi_x > 0);
        assert(dpi_y > 0);

        GUID wic_pixel_format = { 0 };
        hr = wic_frame->GetPixelFormat(&wic_pixel_format);
        verify(hr);

        CComPtr<IWICComponentInfo> wic_comp_info;
        hr = factory_->CreateComponentInfo(wic_pixel_format, &wic_comp_info);
        verify(hr);

        CComPtr<IWICPixelFormatInfo> wic_pixel_format_info;
        hr = wic_comp_info.QueryInterface(&wic_pixel_format_info);
        verify(hr);

        UINT channel_count(0);
        hr = wic_pixel_format_info->GetChannelCount(&channel_count);
        verify(hr);
        assert(channel_count > 0);

        UINT bpp(0);
        hr = wic_pixel_format_info->GetBitsPerPixel(&bpp);
        verify(hr);
        assert(bpp > 0);

        frame_info info;
        info.index = index;
        info.width = width;
        info.height = height;
        info.dpi_x = dpi_x;
        info.dpi_y = dpi_y;
        info.pixel = pixel_info(make_pixel_format_tag(wic_pixel_format), bpp, channel_count);
        info.stride = stride(info.width, info.pixel.bpp);
        return info;
    }

    void read_frame(std::size_t const index, roi_info const& roi, frame_buffer& buffer) const
    {
        assert(index < get_frame_count());
    
        CComPtr<IWICBitmapFrameDecode> wic_frame;
        HRESULT hr = bitmap_decoder_->GetFrame(index, &wic_frame);
        verify(hr);

        frame_info info = get_frame_info(index);

        WICRect wic_rect;
        wic_rect.X = static_cast<INT>(roi.x);
        wic_rect.Y = static_cast<INT>(roi.y);
        wic_rect.Width = std::max<INT>(roi.width, info.width);
        wic_rect.Height = std::max<INT>(roi.height, info.height);

        std::size_t const pixel_buffer_stride = stride(roi.width, info.pixel.bpp);
        std::vector<unsigned char> pixel_buffer(pixel_buffer_stride * roi.height);
        hr = wic_frame->CopyPixels(0, pixel_buffer_stride, pixel_buffer.size(), &pixel_buffer[0]);
        verify(hr);

#if _MSC_VER > 1500
        buffer.pixels = std::move(pixel_buffer);
#else
        buffer.pixels = pixel_buffer;
#endif
        buffer.stride = pixel_buffer_stride;
    }

private:
    CComPtr<IWICImagingFactory> factory_;
    CComPtr<IWICBitmapDecoder> bitmap_decoder_;
    CComPtr<IWICStream> stream_;

    void release()
    {
        stream_.Release();
        bitmap_decoder_.Release();
        factory_.Release();
    }

    void verify(HRESULT const hr) const
    {
        if (FAILED(hr))
            throw hr;
    }

    std::size_t stride(std::size_t const width, std::size_t const bpp) const
    {
        assert(0 == bpp % 8);

        std::size_t const byte_count = bpp / 8;
        std::size_t const stride = (width * byte_count + 3) & ~3;

        assert(0 == stride % sizeof(DWORD));
        return stride;
    }
    
    std::wstring make_unicode(std::string const& s) const
    {
        std::size_t ssize = s.size();
        wchar_t* wbuf = new wchar_t[ssize + 1];
        wbuf[ssize] = L'\0';
        MultiByteToWideChar(CP_ACP, 0, s.c_str(), -1, wbuf, static_cast<int>(ssize));
        std::wstring ws;
        try
        {
            ws.assign(wbuf);
            delete[] wbuf;
        }
        catch (...)
        {
            delete[] wbuf;
            throw;
        }
        return ws;
    }
};

#endif // JXRCXX_IMPLEMENTATION_WIC_ENABLED

} // namespace detail

decoder::decoder(codec::tag const& codec)
{
#ifdef JXRCXX_IMPLEMENTATION_WIC_ENABLED
    if (codec == codec::wic)
    {
        strategy_ = strategy_ptr(new detail::decoder_wic());
    }
    else
#endif // JXRCXX_IMPLEMENTATION_WIC_ENABLED
    {
        strategy_ = strategy_ptr(new detail::decoder_reference());
    }

    assert(strategy_);
}

void decoder::attach(char const* const filename)
{
    assert(strategy_);
    assert(filename);
    return strategy_->attach(filename);
}

std::size_t decoder::get_frame_count() const
{
    assert(strategy_);
    std::size_t const c = strategy_->get_frame_count();
    assert(c > 0);
    return c;
}

frame_info decoder::get_frame_info(std::size_t const index) const
{
    assert(strategy_);
    assert(index < get_frame_count());
    return strategy_->get_frame_info(index);
}

void decoder::read_frame(std::size_t const index, frame_buffer& buffer) const
{
    //TODO
    //frame_info fi = get_frame_info(index);
    //roi_info roi;
    //roi.
    //read_frame(index, roi, buffer);
}

void decoder::read_frame(std::size_t const index, roi_info const& roi, frame_buffer& buffer) const
{
    assert(strategy_);
    assert(index < get_frame_count());
    strategy_->read_frame(index, roi, buffer);
}

} // namespace jxrpp