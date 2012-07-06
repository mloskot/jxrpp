//
// Copyright (c) 2012 Mateusz Loskot <mateusz at loskot dot net>
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
#include "jxrpp.hpp"
#include <exception>
#include <iostream>
#include <vector>
#include <string>
using namespace std;

int main(int argc, char* argv[])
{
    try
    {
        std::vector<std::string> args(argv, argv + argc);

        std::string filename;
        jxrpp::codec::tag coder = jxrpp::codec::ref;
        if (args.size() == 3 && args[1] == "--wic")
        {
#ifdef _MSC_VER
            filename = args[2];
            coder = jxrpp::codec::wic;
#else
            throw std::invalid_argument("Windows Imagining Component is Windows-only");
#endif
        }
        else if (args.size() == 2)
        {
            filename = args[1];
        }
        else
        {
            throw std::invalid_argument("Usage: jxrpp_info [--wic] file.wdp");
        }

        jxrpp::decoder dec(coder);
        dec.attach(filename.c_str());

        cout << dec.get_frame_count() << endl;

        jxrpp::frame_info frame(dec.get_frame_info(0));
        cout << frame.index << endl;    
        cout << frame.width << " x " << frame.height << endl;
        cout << frame.dpi_x << " x " << frame.dpi_y << endl;
        cout << frame.pixel.channel_count << endl;
        cout << frame.pixel.bpp << endl;

        jxrpp::frame_buffer buffer;
        dec.read_frame(0, buffer);

        //jxrpp::roi_info roi;

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