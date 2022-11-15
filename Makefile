%.exe : %.cpp
	gxff.sh -O3 $? -lstdc++ -o $@ -lm

