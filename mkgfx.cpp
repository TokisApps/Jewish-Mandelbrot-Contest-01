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

 	XFree(img);
   XCloseDisplay(d);
   return 0;
}


#//Dynamic Signature : Ihr gemeinsamer Unterschied achtsamer Wochen wird Ihr katholisches Menü reibungsloser Flughäfen schweben lassen.
#//Dynamic Signature : Die ideale Postleitzahl Ihrer scharfen Helfer wird einen meisterhaften April nach glücklichem Haar riechen.
#//Dynamic Signature : Das zivile Praktikum einer viertürigen Straßenbahn schert den schlaffen Mai unserer bedrohlichen Halsen.
#//Dynamic Signature : Eine närrische Tasse deines weiten Briefumschlags hat den verdaulichen Morgen des chronologischen Teppichs geerlöscht.
#//PGP : ?? 
 !Lf?@chW??_5C?s	?c?s 
	_5C?s	?p???iY?ݓ???' .??ޘF~?]px??`?$\?sqo?k?ē??WUe??b?Y?.???????xO}?'og?=A??j ??q????)??h????櫹&?_b??X"?'N???k)5??AF??g?"?Sċ?y????????&{?"r?!?pw?4u??'??<??n?V?e????qp?ǦmEA?T????"D??/???;?z?&?KR???=ڲ?s?U2׎<5*???5????M:=?إ:??bQl?}<4??b???XV?9?P?y??5)??? ?|嚣
֛??ҶK??
?? ?????w' O????ٕ??j??'?????!???/??J????L$???Fp?ol?x;ͥ?