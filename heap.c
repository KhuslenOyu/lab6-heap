#include "DS.h"

static void swim(Heap *p, int);
static void sink(Heap *p, int);

/*
  Хоёр зурвасын чухлыг харьцуулах функц.
  b нь илүү чухал бол 1, бусад үед 0-ыг буцаах функц.
  Өөрөөр хэлбэл a < b үйлдэл юм.
*/
int less(const Msg *a, const Msg *b)
{
  if(a->priority !=priority)
      return a->priority > b->priority;
  return a->time > b->time;
}
static void exch(Heap *p, int i, int j){
  Msg tmp = p->h_arr[i];
  p->h_arr[i] = p->h_arr[j];
  p->h_arr[j] = tmp;
}
/*
  Оруулах функц. heap зарчмаар чухлын дарааллыг баримтлан оруулна.
  Ингэхдээ хамгийн чухал зурвас heap-ын оройд хадгалагдана.
  x зурвасыг p-ын зааж буй heap бүтцэд оруулна.
 */
void insert(Heap *p, const Msg x)
{
    p->h_arr[p->h_len] = x;
    p->h_len++;
    swim(p, p->h_len-1);
}

/*
  Heap бүтцийн swim үйлдэл.
  k нь swim үйлдлийг p-ын зааж буй heap дээр эхлүүлэх индекс.
 */
static void swim(Heap *p, int k)
{
    while (k > 0 && less(&p->h_arr[(k - 1) / 2], &p->h_arr[k]))
    {
        exch(p, k, (k - 1) / 2);
        k = (k - 1) / 2;
    }
}

/*
  Heap бүтцийн sink үйлдэл.
  k нь sink үйлдлийг p-ын зааж буй heap дээр эхлүүлэх индекс.
 */
static void sink(Heap *p, int k)
{
  int n = p->h_len;
  while(2*k + 1 <n)
  {
    int j = 2 * k + 1;
    if (j + 1 < n && less(&p->h_arr[j], &p->h_arr[j + 1]))
            j++; 
    if (!less(&p->h_arr[k], &p->h_arr[j]))
            break;
    exch(p, k, j);
        k = j;
  }
}

/*
  p-ын зааж буй heap бүтцээс оройн элементийг гаргаад буцаах функц.
  Гаргасны дараа орой бүрийн хувьд heap зарчим хадгалах ёстой.
 */
Msg delMin(Heap *p)
{
  Msg min = p->h_arr[0];
  p->h_len--;
  p->h_arr[0] = p->h_arr[p->h-len];
  sink(p, 0);
  return min;
}

