gensent : gs.cpp
  cat gs.cpp | sed -e "s/\\\"/\\\\\"/g" | sed -e "s/.*/\"\0\", /" > src.hpp
  gcc -O3 gs.cpp -lstdc++ -lX11 -lcrypto -lpulse -lpulse-simple -o gensent
  
  
  
