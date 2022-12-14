#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
 
#include <pulse/simple.h>
#include <pulse/error.h>
 
#define BUFSIZE 1000

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
		const unsigned long long n = sizeof(randseed) * 8;

	unsigned long long tmp1 = randseed;

	for(int k = 0;k < 3;++k) {
		unsigned long long x = tmp1;
		int m = ((tmp1 + randseed) % n) - 3;
		if(m <= 0) m = 1;
		for(long long i = 0;i < m;++i) {
			unsigned long long b = x & 1ULL;
			x >>= 1ULL;
			x |= b << (unsigned long long)(n - 2ULL);
		}
		tmp1 ^= x;
		//cout << "rs : " << randseed << " x : " << x << endl;
	}
	randseed = tmp1;
	return randseed % ((long long)RAND_MAX + 1ULL);
}

long long _srand() {
	stringstream ss;
	Display *display = XOpenDisplay(NULL);
if(display) {
	Window rootWindow = RootWindow(display, DefaultScreen(display));    
	XWindowAttributes attrs;
	XGetWindowAttributes(display, rootWindow, &attrs);
	XImage *image = XGetImage( display, rootWindow, 0, 0, attrs.width, attrs.height, AllPlanes, ZPixmap);
if(image) {
	ss << "Image { width : " << attrs.width << "; height : " << attrs.height << ";32bit ??;} = {";
	for (long long i = 0; i < attrs.height; ++i) {
		for (long long j = 0; j < attrs.width; ++j) {
			ss << XGetPixel(image, j, i);
		}
	}
	ss << "}" << endl;
        XFree(image);
}
}
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
	for (long long i = 0;i < 441;++i) {
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

#//Dynamic Signature : Mehrere akkuraten Sekret??rinen der ehrerbietigen ??bernachtung springen eine h??ndische Pause der ultrakurzen Ticketen .
#//PGP : ?? 
 !Lf?@chW??_5C?s	?c?I 
	_5C?s	?? ??$Y$Auz?-a6?m]?\G<??Y?P6???v???rp	???b?[R?????7a?>??-"y?
???5?<?}???kH?w{?m~???LI[??????A???U??? P??n?V?L?,???4????/???x?6?J??9Wj???u?????N??9?8K??|???c98???x?a??????
???5?F\??f,,?X?t|?-?mN?o}??/M??~(?~????GO?????7?Bx ?*_%e??Yd????M??7?B?X?	??9o??t?51??? |?S,???:n/?<r????e??\??`Z?I???N????g7?'??C??????????j??B!o/x??m????I????"?| ????@+g9??i?]L??'