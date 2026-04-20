union _a {
	struct {int aa:16;	int aaa:16; };
	int val;
};
union _b {
	struct {int bb:16;	int bbb:16; };
	int val;
};
union _c {
	struct {int cc:16;	int ccc:16; };
	int val;
};

struct mmio_map {
	union _a a;	union _b b;	union _c c;
};

int driver_init(void *base_addr);
int driver_func(void);
