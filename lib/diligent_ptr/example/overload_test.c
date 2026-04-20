#include <stdio.h>

struct size {
	int width;
	int height;

	size() : width(640), height(480) { }
};

struct metrics {
	size s;

	size const *operator->() const {
		printf("2\n");
		return &s;
	}
};

struct screen {
	metrics m;

	metrics operator->() const {
		printf("1 ");
		return m;
	}
};

int main(void) {
	screen s;

	printf("%d\n", s->width);
}
