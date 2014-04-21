#ifndef ADJACENCY_H
#define ADJACENCY_H

#ifdef __cplusplus
extern "C"
#endif

void create_adjacency_table(uint32_t size);

void insert_neighbours(uint32_t a, uint32_t b, uint32_t c);

int32_t find_neighbour(uint32_t a, uint32_t b);

void delete_adjacency_table();

#ifdef __cplusplus
}
#endif
#endif /* ADJACENCY_H */
