//
// Copyright (c) 2012 Mateusz Loskot <mateusz at loskot dot net>
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
#ifndef JXRCXX_JXRCXX_HPP_INCLUDED
#define JXRCXX_JXRCXX_HPP_INCLUDED

#ifdef _MSC_VER
#define JXRCXX_IMPLEMENTATION_WIC_ENABLED
#endif

#include <guiddef.h>
#include <memory>
#include <vector>

namespace jxrcxx
{

struct codec
{
	enum tag
	{
		reference
#ifdef JXRCXX_IMPLEMENTATION_WIC_ENABLED
		, wic // Windows Imaging Component (WIC)
#endif
	};
};


// Pixel format enumerators generated from WICPixelFormatGUID.
struct pixel_info
{
	enum tag
	{
		undefined = 0,
		dontcare = undefined,
		blackwhite,
		bpp1_indexed,
		bpp2_gray,
		bpp2_indexed,
		bpp4_gray,
		bpp4_indexed,
		bpp8_alpha,
		bpp8_gray,
		bpp8_indexed,
		bpp16_bgr555,
		bpp16_bgr565,
		bpp16_bgra5551,
		bpp16_gray,
		bpp16_gray_fixedpoint,
		bpp16_gray_half,
		bpp24_bgr,
		bpp24_channels3,
		bpp24_rgb,
		bpp32_bgr,
		bpp32_bgr101010,
		bpp32_bgra,
		bpp32_channels3_alpha,
		bpp32_channels4,
		bpp32_cmyk,
		bpp32_gray_fixedpoint,
		bpp32_gray_float,
		bpp32_pbgra,
		bpp32_prgba,
		bpp32_rgba,
		bpp32_rgba1010102,
		bpp32_rgba1010102_xr,
		bpp32_rgbe,
		bpp40_channels4_alpha,
		bpp40_channels5,
		bpp40_cmyk_alpha,
		bpp48_bgr,
		bpp48_bgr_fixedpoint,
		bpp48_channels3,
		bpp48_channels5_alpha,
		bpp48_channels6,
		bpp48_rgb,
		bpp48_rgb_fixedpoint,
		bpp48_rgb_half,
		bpp56_channels6_alpha,
		bpp56_channels7,
		bpp64_bgra,
		bpp64_bgra_fixedpoint,
		bpp64_channels3_alpha,
		bpp64_channels4,
		bpp64_channels7_alpha,
		bpp64_channels8,
		bpp64_cmyk,
		bpp64_pbgra,
		bpp64_prgba,
		bpp64_rgb_fixedpoint,
		bpp64_rgb_half,
		bpp64_rgba,
		bpp64_rgba_fixedpoint,
		bpp64_rgba_half,
		bpp72_channels8_alpha,
		bpp80_channels4_alpha,
		bpp80_channels5,
		bpp80_cmyk_alpha,
		bpp96_channels5_alpha,
		bpp96_channels6,
		bpp96_rgb_fixedpoint,
		bpp112_channels6_alpha,
		bpp112_channels7,
		bpp128_channels7_alpha,
		bpp128_channels8,
		bpp128_prgba_float,
		bpp128_rgb_fixedpoint,
		bpp128_rgb_float,
		bpp128_rgba_fixedpoint,
		bpp128_rgba_float,
		bpp144_channels8_alpha
	};

	tag format_tag;
	std::size_t bpp; // bits per pixel
	std::size_t channel_count;

	pixel_info() : format_tag(undefined), bpp(0), channel_count(0) {}
	pixel_info(pixel_info::tag tag, std::size_t bpp, std::size_t channel_count)
		: format_tag(tag), bpp(bpp), channel_count(channel_count) {}
};

struct frame_info
{
	pixel_info pixel;
	double dpi_x;
	double dpi_y;
	std::size_t index;
	std::size_t width;
	std::size_t height;
	std::size_t stride;

    frame_info() : dpi_x(0), dpi_y(0), index(0), width(0), height(0), stride(0) {}
};

struct roi_info
{
	std::size_t x;
	std::size_t y;
	std::size_t width;
	std::size_t height;

	roi_info() : x(0), y(0), width(0), height(0) {}
};

struct frame_buffer
{
	typedef std::vector<unsigned char> buffer_type;
	buffer_type pixels;
	std::size_t stride; // TODO replace with frame_info

	frame_buffer() : stride(0) {}
};

namespace detail
{
	class decoder_base;
} // namespace detail

class decoder
{
public:
	explicit decoder(codec::tag const& codec);
	void attach(char const* const filename);
	std::size_t get_frame_count() const;
	frame_info get_frame_info(std::size_t const index) const;
	void read_frame(std::size_t const index, roi_info const& roi, frame_buffer& buffer) const;

private:
	// noncopyable
	decoder(decoder const& other);
	decoder& operator=(decoder const& other);

	typedef std::shared_ptr<detail::decoder_base> strategy_ptr;
	strategy_ptr strategy_;
};

} // namespace jxrcxx

#endif // JXRCXX_JXRCXX_HPP_INCLUDED
