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

## Pre-Requirements

(1) Lame library ver 3.100 and later; Download it from here : http://lame.sourceforge.net/

## How to build
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

	    
