Donkey Kong (OOP Project with Allegro) 

[![Watch the video](https://i.imgur.com/ST0QkxC.png)](https://www.youtube.com/watch?v=RMV6-3SdDWg&t=11s)

compile in source with:

g++ *.cpp $(pkg-config allegro-5 allegro_font-5 allegro_image-5 allegro_memfile-5 allegro_ttf-5 allegro_physfs-5 allegro_dialog-5 allegro_video-5 allegro_acodec-5 allegro_main-5 allegro_primitives-5 allegro_audio-5 --libs --cflags)

or

g++ -std=c++11 *.cpp $(pkg-config allegro-5 allegro_font-5 allegro_image-5 allegro_memfile-5 allegro_ttf-5 allegro_physfs-5 allegro_dialog-5 allegro_video-5 allegro_acodec-5 allegro_main-5 allegro_primitives-5 allegro_audio-5 --libs --cflags)

