#include "DS.h"

static void swim(Heap *p, int k);
static void sink(Heap *p, int k);
static void exch(Heap *p, int i, int j);

/*
  a нь b-ээс бага чухал бол 1 буцаана.
  priority бага бол илүү чухал.
  priority тэнцүү бол time бага нь түрүүлнэ.
*/
int less(const Msg *a, const Msg *b)
{
    if (a->priority != b->priority)
        return a->priority > b->priority;

    return a->time > b->time;
}

static void exch(Heap *p, int i, int j)
{
    Msg temp = p->h_arr[i];
    p->h_arr[i] = p->h_arr[j];
    p->h_arr[j] = temp;
}

static void swim(Heap *p, int k)
{
    while (k > 0) {
        int parent = (k - 1) / 2;

        if (!less(&p->h_arr[parent], &p->h_arr[k]))
            break;

        exch(p, parent, k);
        k = parent;
    }
}

static void sink(Heap *p, int k)
{
    while (2 * k + 1 < p->h_len) {
        int child = 2 * k + 1;

        if (child + 1 < p->h_len &&
            less(&p->h_arr[child], &p->h_arr[child + 1])) {
            child++;
        }

        if (!less(&p->h_arr[k], &p->h_arr[child]))
            break;

        exch(p, k, child);
        k = child;
    }
}

void insert(Heap *p, const Msg x)
{
    if (p->h_len >= 100000)
        return;

    p->h_arr[p->h_len] = x;
    p->h_len++;

    swim(p, p->h_len - 1);
}

Msg delMin(Heap *p)
{
    Msg result = p->h_arr[0];

    p->h_len--;

    if (p->h_len > 0) {
        p->h_arr[0] = p->h_arr[p->h_len];
        sink(p, 0);
    }

    return result;
}
