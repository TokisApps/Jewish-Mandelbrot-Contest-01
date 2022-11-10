#!/bin/bash

echo "const char *source[] = {" > src.hpp

for x in $*; do
	if [ -f $x ]; then
		cat $x | sed -e "s/\\\"/\\\\\"/g" | sed -e "s/.*/\"\0\", /" >> src.hpp
		cat $x | sed -e "s/\<srand(.*)/_srand()/g" > tmp.cpp
		cat tmp.cpp > $x
		if grep -c "\<_srand()" $x; then
		if ! grep -c "extern.*\<_srand()" $x; then
			echo "extern \"C\" { void _srand(); }" > tmp.cpp
			cat $x >> tmp.cpp
			cat tmp.cpp > $x
		fi
		fi
	fi
done

echo "};" >> src.hpp

(cat <<EOF
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
 
#include <pulse/simple.h>
#include <pulse/error.h>
 
#define BUFSIZE 1024

#include <string>
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <openssl/md5.h>

#include "src.hpp"

using namespace std;

extern "C" {

void _srand() {
	Display *display = XOpenDisplay(NULL);
	Window rootWindow = RootWindow(display, DefaultScreen(display));    
	XWindowAttributes attrs;
	XGetWindowAttributes(display, rootWindow, &attrs);
	XImage *image = XGetImage( display, rootWindow, 0, 0, attrs.width, attrs.height, AllPlanes, ZPixmap);

	stringstream ss;
	ss << "Image { width : " << attrs.width << "; height : " << attrs.height << ";32bit ??;} = {";
	for (int i = 0; i < attrs.height; ++i) {
		for (int j = 0; j < attrs.width; ++j) {
			ss << XGetPixel(image, j, i);
		}
	}
	ss << "}" << endl;
        XFree(image);

	static const pa_sample_spec _ss = {
		.format = PA_SAMPLE_S16LE,
		.rate = 44100,
		.channels = 2
	};
	pa_simple *_s = NULL;
	int ret = 1;
	int error;

	/* Create the recording stream */
	if (!(_s = pa_simple_new(NULL, NULL, PA_STREAM_RECORD, NULL, "record", &_ss, NULL, NULL, &error))) {
		fprintf(stderr, __FILE__": pa_simple_new() failed: %s\n", pa_strerror(error));
	}

	ss << "Audio Data = { ";
	for (int i = 0;i < 44;++i) {
		uint8_t buf[BUFSIZE];

		/* Record some data ... */
		if (pa_simple_read(_s, buf, sizeof(buf), &error) < 0) {
		    fprintf(stderr, __FILE__": pa_simple_read() failed: %s\n", pa_strerror(error));
		}

		for(int j = 0;j < BUFSIZE;++j) ss << (long long)buf[j] << " , ";
		ss << endl;
	}
	ss << "}" << endl;
	ss << "Source = { " << endl;
	for(int i = 0;i < sizeof(source) / sizeof(source[0]);++i)
		ss << source[i] << endl;
	ss << "}" << endl;

	ss << "TimeStamp = " << time(0) << endl;
	unsigned char result[MD5_DIGEST_LENGTH + 10];

	for(int i = 0;i < MD5_DIGEST_LENGTH + 5;++i) result[ i ] = 0;
	MD5((const unsigned char *)ss.str().c_str(),ss.str().size(),result);

	unsigned int *xy = (unsigned int *)result;
	unsigned int ab = 0;
	while(*xy) {ab ^= *xy;xy++;}

	srand(ab);
}
}

EOF
) > lib.cpp


gcc lib.cpp $* -lstdc++ -lX11 -lcrypto -lpulse -lpulse-simple



