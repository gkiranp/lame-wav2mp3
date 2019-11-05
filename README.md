# lame-wav2mp3
C++(11) based wrapper function to Lame-encoder Library.

## Problem Statement
(1) Application is called with pathname as argument, e.g.

<applicationname> F:\MyWavCollection all WAV-files contained directly in that folder are to be encoded to MP3
  
(2) Use all available CPU cores for the encoding process in an efficient way by utilizing multi-threading

(3) Statically link to lame encoder library

(4) Application should be compilable and runnable on Windows and Linux

(5) The resulting MP3 files are to be placed within the same directory as the source WAV files, the filename extension should be changed appropriately to .MP3

(6) Non-WAV files in the given folder shall be ignored

(7) Multithreading shall be implemented in a portable way, for example using POSIX pthreads.

## Prerequisites

-> Lame library ver 3.100 and later; Download it from here : http://lame.sourceforge.net/
### Build Lame encoder library in Linux
	-> Download lame encoder into lame-wav2mp3/src/
	$ tar -xvf lame-3.100.tar.gz
	$ cd lame-3.100
	$ ./configure
	$ make
This will build required lame libraries in Linux. To build lame library in Windows, follow this [link](https://wehuberconsultingllc.com/wordpress/2007/12/30/building-the-lame-mp3-encoder-using-visual-studio-8-express/).

## How to build Wav2Mp3 
Note: To enable debug informations, pass the flag -DDEBUG=ON to cmake build:
	
	$ cmake -DDEBUG=ON ..

### To build in GNU - Linux Environment:
	$ git clone https://github.com/gkiranp/lame-wav2mp3.git
	$ cd lame-wav2mp3/src
	$ mkdir -p build
	$ cd build
	$ cmake ..
	$ make

### To build Microsoft Visual Studio 2013 environment
	> git clone https://github.com/gkiranp/lame-wav2mp3.git
	> cd lame-wav2mp3/src
	> mkdir -p build
	> cd build
	> cmake .. -G "Visual Studio 12 2013"
	> msbuild wav2mp3.vcxproj

### To build using MinGW-32 Windows environment
	> git clone https://github.com/gkiranp/lame-wav2mp3.git
	> cd lame-wav2mp3/src
	> mkdir -p build
	> cd build
	> cmake .. -G "MinGW Makefiles"
	> mingw32-make
	
## To run the application
	$cd lame-wav2mp3/src/build/bin
	$./wav2mp3 <complete-path-to-directory-containing-wav-files>

	    
