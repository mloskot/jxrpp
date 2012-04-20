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

int main(char* argv[], int argc)
{
	try
	{
		//char *const filename = "e:\\data\\test\\jpeg-xr\\jpeg.jpg";
		char *const filename = "e:\\data\\test\\jpeg-xr\\jpeg-xr.wdp";

		jxrcxx::decoder dec(jxrcxx::codec::wic);
		
		dec.initialise(filename);
		cout << dec.frame_count() << endl;

		jxrcxx::frame_details frame_info(dec.frame_info(0));
		cout << frame_info.index << endl;
		cout << frame_info.width << " x " << frame_info.height << endl;
		cout << frame_info.dpi_x << " x " << frame_info.dpi_y << endl;
		cout << frame_info.pixel_info.channel_count << endl;
		cout << frame_info.pixel_info.bpp << endl;

		jxrcxx::frame_data buffer1;
		dec.read(buffer1, 0);

		jxrcxx::frame_data buffer2;
		jxrcxx::roi_details roi(200, 200, 60, 60);
		dec.read(buffer2, 0, roi);

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