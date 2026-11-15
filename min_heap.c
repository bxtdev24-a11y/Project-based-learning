#include "core.h"
#include <limits.h>

typedef struct { int node; int priority; } HeapItem;
typedef struct { HeapItem items[MAX_CELLS * 4]; int size; } MinHeap;

static void swap(HeapItem *a, HeapItem *b) { HeapItem t=*a; *a=*b; *b=t; }
static void push(MinHeap *h, int node, int priority) {
    if (h->size >= MAX_CELLS * 4) return;
    int i = h->size++;
    h->items[i].node=node; h->items[i].priority=priority;
    while (i > 0) {
        int p=(i-1)/2;
        if (h->items[p].priority <= h->items[i].priority) break;
        swap(&h->items[p], &h->items[i]); i=p;
    }
}
static HeapItem pop(MinHeap *h) {
    HeapItem result={-1,INT_MAX};
    if (!h->size) return result;
    result=h->items[0]; h->items[0]=h->items[--h->size];
    int i=0;
    for (;;) {
        int l=2*i+1, r=2*i+2, smallest=i;
        if (l<h->size && h->items[l].priority<h->items[smallest].priority) smallest=l;
        if (r<h->size && h->items[r].priority<h->items[smallest].priority) smallest=r;
        if (smallest==i) break;
        swap(&h->items[i], &h->items[smallest]); i=smallest;
    }
    return result;
}
static int empty(const MinHeap *h) { return h->size == 0; }

/* Public internal API for informed_search.c */
void heap_push_internal(void *heap, int node, int priority) { push((MinHeap*)heap,node,priority); }
void heap_pop_internal(void *heap, int *node, int *priority) {
    HeapItem x=pop((MinHeap*)heap); *node=x.node; *priority=x.priority;
}
int heap_empty_internal(const void *heap) { return empty((const MinHeap*)heap); }
unsigned long heap_storage_size(void) { return sizeof(MinHeap); }
