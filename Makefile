CC=gcc
APPNAME=UnblockMe
CSOURCES=./src/main.c ./src/functions.c ./src/functions.h
LIBS=-lallegro -lallegro_image -lallegro_primitives -lallegro_audio -lallegro_acodec -lallegro_font -lallegro_ttf

all: build

build :
	echo "Building the project now";
	$(CC) $(CSOURCES) $(LIBS) -o $(APPNAME)
	echo "It builds succesfully";
