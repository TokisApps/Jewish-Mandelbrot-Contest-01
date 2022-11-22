#!/bin/bash

while [ true ]; do find $1 -maxdepth 1 -type f -iname "*.norm.*" -printf "mpv --no-video \"%h/%f\"\n" | shuf | bash ;done
#//Dynamic Signature : Der zickige Opa unserer Behelfsferien wirbt für Ihr imaginäres Auto unserer niedrigen Formen.
