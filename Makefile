all: build

build :
	echo "Building the project now";
	gcc ./src/main.c ./src/functions.c ./src/functions.h -o UnblockMe -lallegro -lallegro_image -lallegro_primitives -lallegro_audio -lallegro_acodec -lallegro_font -lallegro_ttf
	echo "It builds succesfully";

