OS := $(shell uname -s)

compile:
	cd Source && \
	g++ -std=c++11 *.cpp -o main `pkg-config allegro-5 allegro_font-5 allegro_image-5 allegro_memfile-5 allegro_ttf-5 allegro_physfs-5 allegro_dialog-5 allegro_video-5 allegro_acodec-5 allegro_main-5 allegro_primitives-5 allegro_audio-5 --libs --cflags`

run:	compile
	cd Source && ./main

run-editor:
	cd DKEditor && gradle desktop:run

clean:
	rm -f Source/main
	cd DKEditor && gradle clean


install-allegro:
ifeq ($(OS),Darwin)
	brew install allegro
else
	sudo apt install liballegro5-dev
endif

install-formatter:
ifeq ($(OS),Darwin)
	brew install clang-format
else
	sudo apt-get install clang-format
endif

dep-install: install-allegro install-formatter

format:
	find . -name '*.cpp' -exec clang-format -style=file -i {} \;
	find . -name '*.h' -exec clang-format -style=file -i {} \;