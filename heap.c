#include "DS.h"

static void swim(Heap *p, int);
static void sink(Heap *p, int);
static void exch(Heap *p, int, int);

/*
Хоёр зурвасын чухлыг харьцуулах функц.
b нь илүү чухал бол 1, бусад үед 0-ыг буцаах функц.
*/
int less(const Msg *a, const Msg *b)
{
    if (a->priority != b->priority)
        return a->priority > b->priority;  // priority жижиг нь илүү чухал
    return a->time > b->time;              // тэнцүү бол эрт ирсэн нь илүү чухал
}

/*
Хоёр индексийн Msg-ийг солих туслах функц (exch).
*/
static void exch(Heap *p, int i, int j)
{
    Msg tmp = p->h_arr[i];
    p->h_arr[i] = p->h_arr[j];
    p->h_arr[j] = tmp;
}

/*
Оруулах функц. heap зарчмаар чухлын дарааллыг баримтлан оруулна.
*/
void insert(Heap *p, const Msg x)
{
    p->h_arr[p->h_len] = x;   // массивын хамгийн төгсгөлд (len-р index) оруулна
    p->h_len++;               // хэмжээг нэмэгдүүлнэ
    swim(p, p->h_len - 1);    // шинэ элементийг зөв байрлал руу "хөвүүлнэ"
}

/*
Heap бүтцийн swim үйлдэл (0-based).
k нь swim үйлдлийг эхлүүлэх индекс.
*/
static void swim(Heap *p, int k)
{
    // k нь root (0) биш, бас эцэг нь өөрөөсөө бага чухал байвал дээш шилжинэ
    while (k > 0 && less(&p->h_arr[(k - 1) / 2], &p->h_arr[k]))
    {
        exch(p, k, (k - 1) / 2);
        k = (k - 1) / 2;
    }
}

/*
Heap бүтцийн sink үйлдэл (0-based).
k нь sink үйлдлийг эхлүүлэх индекс.
*/
static void sink(Heap *p, int k)
{
    int n = p->h_len;
    while (2 * k + 1 < n)             // k-ийн зүүн хүүхэд байгаа эсэх
    {
        int j = 2 * k + 1;            // j = зүүн хүүхдийн индекс
        if (j + 1 < n && less(&p->h_arr[j], &p->h_arr[j + 1]))
            j++;                      // баруун хүүхэд байгаа бөгөөд илүү чухал бол j-г шилжүүл
        if (!less(&p->h_arr[k], &p->h_arr[j]))
            break;                    // k нь хүүхдээсээ илүү чухал буюу тэнцүү бол зогсоно
        exch(p, k, j);
        k = j;
    }
}

/*
p-ын зааж буй heap бүтцээс оройн элементийг гаргаад буцаах функц.
*/
Msg delMin(Heap *p)
{
    Msg min = p->h_arr[0];            // root бол хамгийн чухал зурвас
    p->h_len--;                       // хэмжээг багасгана
    p->h_arr[0] = p->h_arr[p->h_len]; // сүүлийн элементийг root-д тавина
    sink(p, 0);                       // шинэ root-г зөв байрлал руу "live" хийнэ
    return min;
}
