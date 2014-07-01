all: waveflag
clean:
	rm -f waveflag

CFLAGS = -std=c99 -Wall -Wextra `pkg-config --cflags --libs cairo`
LDFLAGS = `pkg-config --libs cairo`
%: %.c
	$(CC) $< -o $@ $(CFLAGS) $(LDFLAGS)
