CC = clang
CFLAGS = -framework CoreMIDI -framework QuartzCore -framework ApplicationServices -lpthread
SRC = midi-scroller-mac.c
OUT = midi-scroller-mac

$(OUT): $(SRC)
	$(CC) $(SRC) -o $(OUT) $(CFLAGS)

clean:
	rm -f $(OUT)