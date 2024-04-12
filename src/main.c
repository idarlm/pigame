#include <stdio.h>
#include <stdlib.h>

const int MAX_ENTITIES = 1000;
const char* PLAYER_NAME = "Player";

struct Entity_Hot *hot_entities;
struct Entity_Cold *cold_entities;
char *index_availability; // TODO: This is wasteful. Make it not so.
int entity_index;

struct Vector3 {
    float x;
    float y;
    float z;
};

struct Entity_Hot {
    struct Vector3 position;
    // struct Quaternion orientation;
    float scale;
};

struct Entity_Cold {
    int id;
};

struct Entity {
    struct Entity_Hot *hot;
    struct Entity_Cold *cold;
};

struct Player {
    struct Entity entity;
};

void alloc_entity_pool(int size) {
    entity_index = 0;
    hot_entities = (struct Entity_Hot*)malloc(sizeof(struct Entity_Hot[size]));
    cold_entities = (struct Entity_Cold*)malloc(sizeof(struct Entity_Cold[size]));
    index_availability = (char*)malloc(sizeof(char[size]));

    // init index_availability
    for (int i = 0; i < size; i++) {
        (*(index_availability + i)) = 0;
    }
}

void free_entity_pool() {
    free(hot_entities);
    free(cold_entities);
}

int assign_entity(struct Entity *e) {
    if (entity_index == MAX_ENTITIES) {
        return 0;
    }
    struct Entity_Hot *hot = (hot_entities + entity_index);
    hot->position.x = 0.f;
    hot->position.y = 0.f;
    hot->position.z = 0.f;
    hot->scale = 1.f;

    struct Entity_Cold *cold = (cold_entities + entity_index);
    cold->id = entity_index;

    (*(index_availability + entity_index)) = 1;

    e->hot = hot;
    e->cold = cold;
    entity_index++;
    return 1;
}

int assign_entity_by_id(struct Entity *e, int id) {
    e->hot = (hot_entities + id);
    e->cold = (cold_entities + id);
    return (*(index_availability + id));
}

void free_entity(int id) {
    (*(index_availability + id)) = 0;
}

int main(int* argc, char** argv) {
    alloc_entity_pool(MAX_ENTITIES);

    int count = 0;
    int success = 1;
    while ( success ) {
        struct Entity e;
	success = assign_entity(&e);
	printf("created entity %d: pos.x=%f, scale=%f, id=%d\n", ++count, e.hot->position.x, e.hot->scale, e.cold->id);
    }

    struct Entity e;
    success = assign_entity_by_id(&e, 42);
    if (success) {
        printf("entity with id 42: id=%d\n", e.cold->id);
    }

    free_entity(42);

    success = assign_entity_by_id(&e, 42);
    if (success) {
        printf("entity with id 42: id=%d\n", e.cold->id);
    } else {
        printf("entity with id 42 does not exist.\n");
    }

    free_entity_pool();
    return 0;
}
