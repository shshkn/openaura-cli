CC = g++
CFLAGS =
INCLUDE = -Isrc/OpenAuraSDK -Isrc/include

SOURCES = src/OpenAuraSDK/*.cpp src/main.cpp
ODIR = build
BIN = openaura-cli

build:
	$(CC) $(CFLAGS) $(INCLUDE) $(SOURCES) -o $(ODIR)/$(BIN)

clean:
	rm -f $(ODIR)/*

.PHONY: build clean
