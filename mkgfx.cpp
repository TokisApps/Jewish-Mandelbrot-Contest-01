extern "C" { long long _rand(); }
extern "C" { long long _srand(); }
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <unistd.h>

using namespace std;

int main(void) {
   Display *d;
   Window win;
   XEvent e;
   const char *msg = "Hello, World!";
   int s;

   d = XOpenDisplay(NULL);
   if (d == NULL) {
      fprintf(stderr, "Cannot open display\n");
      exit(1);
   }

   s = DefaultScreen(d);
   const int w = 400;
   const int h = 300;

   win = XCreateSimpleWindow(d, RootWindow(d, s), 10, 10, w, h, 1,
                           BlackPixel(d, s), WhitePixel(d, s));

     XMapWindow(d, win);
			while(XPending(d));

     XImage *img = XGetImage(d,RootWindow(d, s),0,0,w,h,AllPlanes,ZPixmap);


 while (1) {

	 _srand();

	 for(int i = 0;i < w - 10;++i) {
		 for(int j = 0;j < h - 10;++j) {
			 	XPutPixel(img,i,j,_rand() + RAND_MAX * _rand());
	 
		 }
	}

	 XPutImage(d,win,DefaultGC(d, 0),img,0,0,0,0,w,h);
			while(XPending(d));
   }

   XCloseDisplay(d);
   return 0;
}


