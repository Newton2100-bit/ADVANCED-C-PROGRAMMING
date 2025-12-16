union < name of the union> {
	< your data types will go here >
};


enum Type { INT, FLOAT, STRING };
struct Value {
    enum Type type;
    union {
        int i;
        float f;
        char *s;
    } data;
};

use case 

struct Value v;
v.type = FLOAT;
v.data.f = 3.14;
