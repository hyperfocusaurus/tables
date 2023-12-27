CFLAGS := -Wall -Wextra -std=c11 -ggdb -Iraylib/src
LDFLAGS := -lm -lglfw -lGL -lpthread -ldl
LD := gcc


tables: main.o table.o raylib/src/libraylib.a
	$(LD) -o tables $^ $(LDFLAGS)

clean:
	rm -f *.o tables

raylib/src/libraylib.a:
	$(MAKE) PLATFORM=PLATFORM_DESKTOP -C raylib/src
