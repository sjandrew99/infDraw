# infDraw
2d-drawing software for creating, eg, flow charts (draw lines, boxes, etc, snap connections, infinitely-expanding canvas)

#installation:
 - I've only tested this on Ubuntu 18
 - Prereqs: gtk3, opencv2, json
     - using json parser: https://github.com/nlohmann/json
        git clone https://github.com/nlohmann/json.git
        cd json/
        git status
        mkdir build
        cd build
        cmake ..
        make
        sudo make install

# usage:
 start: ./infDraw
 key bindings: 
   's': select mode
   'l': draw line 
   'b': draw box


