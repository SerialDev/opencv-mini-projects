sudo apt-get update  
sudo apt-get install libopencv-dev python3-opencv  
mkdir build && cd build && cmake .. && make  


/rtags/bin/rc -J /opencv-mini-projects/build/compile_commands.json
