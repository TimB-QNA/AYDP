#!/bin/bash

/usr/games/fgfs \
  --fg-root=/usr/share/games/flightgear \
  --fg-scenery=/usr/share/games/flightgear/Scenery \
  --fg-aircraft=/usr/share/games/flightgear/Aircraft/ \
  --airport=EGGP \
  --aircraft=Cub \
  --disable-fullscreen \
  --prop:/sim/rendering/random-vegetation=false \
  --disable-ai-models \
  --disable-ai-traffic \
  --disable-real-weather-fetch \
  --prop:/sim/menubar/autovisibility/enabled=1 \
  --bpp=32 \
  --time-match-real \
  --enable-terrasync \
  --disable-fgcom \
  --generic=socket,out,10,localhost,7000,tcp,FOAI-proto \
  --generic=socket,in,10,localhost,7100,tcp,FIAO-proto
