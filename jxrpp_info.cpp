//
// Copyright (c) 2012 Mateusz Loskot <mateusz at loskot dot net>
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
#include "jxrcxx.hpp"
#include <exception>
#include <iostream>
using namespace std;

int main(int argc, char* argv[])
{
    try
    {
        char const* filename = "e:\\data\\test\\jpeg-xr\\jpeg-xr.wdp";
#ifdef _MSC_VER
        jxrcxx::decoder dec(jxrcxx::codec::wic);
#else
        jxrcxx::decoder dec(jxrcxx::codec::reference);
#endif
        dec.attach(filename);

        cout << dec.get_frame_count() << endl;

        jxrcxx::frame_info frame(dec.get_frame_info(0));
        cout << frame.index << endl;
        cout << frame.width << " x " << frame.height << endl;
        cout << frame.dpi_x << " x " << frame.dpi_y << endl;
        cout << frame.pixel.channel_count << endl;
        cout << frame.pixel.bpp << endl;

        jxrcxx::frame_buffer buffer;
        jxrcxx::roi_info roi;
        dec.read_frame(0, roi, buffer);


        return EXIT_SUCCESS;
    }
    catch (std::exception const& e)
    {
        std::cerr << e.what() << std::endl;
    }
    catch (...)
    {
        std::cerr << "unhandled error" << std::endl;
    }

    return EXIT_FAILURE;
}