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

