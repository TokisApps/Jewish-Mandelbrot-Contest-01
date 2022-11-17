#!/bin/bash

echo "const char *source[] = {" > src.hpp

for z in srand rand; do
for y in ${*%.cpp}; do
	x=$y.cpp
	if [ -f $x ]; then
		cat $x | sed -e "s/\\\"/\\\\\"/g" | sed -e "s/.*/\"\0\", /" >> src.hpp
		cat $x | sed -re "s/\<$z[(][^)]*[)]/_$z()/g" > tmp.cpp
		cat tmp.cpp > $x
		if grep -c "\<_$z()" $x; then
		if ! grep -c "extern.*\<_$z()" $x; then
			echo "extern \"C\" { long long _$z(); }" > tmp.cpp
			cat $x >> tmp.cpp
			cat tmp.cpp > $x
		fi
		fi
	fi
done
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

static unsigned long long randseed = 0;

long long _rand() {
	//cout << "**** bit shuffle ***** (rs : " << randseed << ")" << endl;

	for(int k = 0;k < 10;++k) {
		unsigned long long x = 0;
		const int n = sizeof(randseed) * 8;
		/*for(long long i = 0;i < n;++i) {
			x |= ((long long)(randseed >> (long long)(n - i - 1)) & 1LL) << i;
		}*/
		x = randseed;
		int m = (x % n) / 2;
		if(m == 0) m = 1;
		for(long long i = 0;i < m;++i) {
			unsigned long long b = randseed & 1LL;
			randseed >>= 1LL;
			randseed |= b << (long long)(n - 2LL);
		}
		randseed ^= x;
		//cout << "rs : " << randseed << " x : " << x << endl;
	}
	return randseed % ((long long)RAND_MAX + 1LL);
}

long long _srand() {
	Display *display = XOpenDisplay(NULL);
	Window rootWindow = RootWindow(display, DefaultScreen(display));    
	XWindowAttributes attrs;
	XGetWindowAttributes(display, rootWindow, &attrs);
	XImage *image = XGetImage( display, rootWindow, 0, 0, attrs.width, attrs.height, AllPlanes, ZPixmap);

	stringstream ss;
	ss << "Image { width : " << attrs.width << "; height : " << attrs.height << ";32bit ??;} = {";
	for (long long i = 0; i < attrs.height; ++i) {
		for (long long j = 0; j < attrs.width; ++j) {
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
	long long ret = 1;
	int error;

	/* Create the recording stream */
	if (!(_s = pa_simple_new(NULL, NULL, PA_STREAM_RECORD, NULL, "record", &_ss, NULL, NULL, &error))) {
		fprintf(stderr, __FILE__": pa_simple_new() failed: %s\n", pa_strerror(error));
	}
if(_s) {
	ss << "Audio Data = { ";
	for (long long i = 0;i < 44;++i) {
		uint8_t buf[BUFSIZE];

		/* Record some data ... */
		if (pa_simple_read(_s, buf, sizeof(buf), &error) < 0) {
		    fprintf(stderr, __FILE__": pa_simple_read() failed\n");
		}

		for(long long j = 0;j < BUFSIZE;++j) ss << (long long)buf[j] << " , ";
		ss << endl;
	}
	ss << "}" << endl;
pa_simple_free(_s);
}
	ss << "Source = { " << endl;
	for(long long i = 0;i < sizeof(source) / sizeof(source[0]);++i)
		ss << source[i] << endl;
	ss << "}" << endl;

	ss << "TimeStamp = " << time(0) << endl;
	unsigned char result[MD5_DIGEST_LENGTH + 10];

	for(long long i = 0;i < MD5_DIGEST_LENGTH + 5;++i) result[ i ] = 0;
	MD5((const unsigned char *)ss.str().c_str(),ss.str().size(),result);

	unsigned long long *xy = (unsigned long long *)result;
	unsigned long long ab = 0;
	while(*xy) {ab ^= *xy;xy++;}

	randseed = ab;
	cout << "seed : " << randseed << endl;

	return 0;
}
}

EOF
) > lib.cpp


gcc lib.cpp $* -lstdc++ -lX11 -lcrypto -lpulse -lpulse-simple



