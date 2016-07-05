// mineswept.h -- the header file
#ifndef MINESWEPT_H_
#define MINESWEPT_H_
class node
{
private:
  int  ord;
  node * next;
public:  node() {ord=0;next=0;}
  node(int p, node * t = 0)  {ord=p;next=t;}
  node * add(int p)  {next = new node (p);return next;}
  node * add(node * n) {next = n;return next;}
  int get_ord() {return ord;}
  node * get_next() {return next;}
  void set_next(node * pnode) {next=pnode;}
  void set_ord(int o) {ord=o;}
  ~node() {};
};
class hdtl
{
private:
  int num;
  int ord;
  node * head;
  node * tail;
public: hdtl() {head=0;tail=0;num=1;ord=0;}
  hdtl(node * p,int n1, int n2)
  {head=p;tail=p;num=n1;ord=n2;}
  hdtl(node * p1, node * p2,int n1, int n2)
  {head=p1;tail=p2;num=n1;ord=n2;}
  node * get_head() {return head;}
  node * get_tail() {return tail;}
  int get_num() {return num;}
  int get_ord() {return ord;}
  void seth(node * h)  {head = h;}
  void setl(node * t)  {tail = t;}
  void setn(int n) {num=n;}
  void seto(int o) {ord=o;}
  void add(int p) {tail=tail->add(p);num++;}
  void add(node * n) {tail=tail->add(n);}
  int joint(hdtl * h1)
  {
    if (num>h1->get_num())
      {
	tail->set_next(h1->get_head());
	tail = h1->get_tail();
	num += h1->get_num();
	h1->seto(ord);
      }
    else
      {
	node * temp=h1->get_tail();
	temp->set_next(head);
	h1->setl(tail);
	h1->setn(num+h1->get_num());
	ord=h1->get_ord();
      }
    return ord;
  }
  ~hdtl() {};
};
typedef node * linkn;
typedef hdtl * linkh;

#endif
