template <class T> class olist;

#ifndef OLIST_H
#define OLIST_H

template <class T> class olist {
private:
  struct node_base {
    node_base(node_base *p = nullptr, node_base *n = nullptr);
    virtual ~node_base();
    node_base *prev, *next;
  };

  struct node : public node_base {
    node(const T &o, node_base *p = nullptr, node_base *n = nullptr);

    T obj;
  };

public:
  class const_iterator;
  class iterator {
    friend class olist<T>;
    friend class const_iterator;
    node_base *ptr;
    iterator(node_base *p);

  public:
    iterator(const iterator &it);
    bool operator==(const const_iterator &other) const;
    bool operator!=(const const_iterator &other) const;
    iterator &operator++();
    iterator operator++(int);
    iterator &operator--();
    iterator operator--(int);
    const T &operator*() const;
    const T *operator->() const;
  };

  class const_iterator {
    friend class olist<T>;
    node_base *ptr;
    const_iterator(node_base *p);

  public:
    const_iterator(const const_iterator &cit);
    const_iterator(const iterator &it);
    bool operator==(const const_iterator &other) const;
    bool operator!=(const const_iterator &other) const;
    const_iterator &operator++();
    const_iterator operator++(int);
    const_iterator &operator--();
    const_iterator operator--(int);
    const T &operator*() const;
    const T *operator->() const;
  };

private:
  unsigned int _size;
  node_base *pte;

public:
  olist();
  olist(const olist &);
  ~olist();

  // Since items in a ordered container can't be modified directly, T &front()
  // and T &back() are not declared
  const T &front() const;
  const T &back() const;
  iterator begin();
  const_iterator begin() const;
  iterator end();
  const_iterator end() const;
  bool empty() const;
  unsigned int size() const;
  void clear();
  iterator insert(const T &obj);
  iterator insert(const T &obj, iterator hint);
  iterator insert(const T &obj, const_iterator hint);
  void erase(iterator pos);
  void erase(const_iterator pos);
  void pop_back();
  void pop_front();
  void pop(const_iterator pos);
  void merge(olist &other);
  bool contains(const T &obj) const;

  olist &operator=(const olist &other);
  bool operator==(const olist &other);
};

template <class T>
olist<T>::node_base::node_base(node_base *p, node_base *n) : prev(p), next(n) {}

template <class T> olist<T>::node_base::~node_base() = default;

template <class T>
olist<T>::node::node(const T &o, node_base *p, node_base *n)
    : node_base(p, n), obj(o) {}

template <class T> olist<T>::iterator::iterator(node_base *p) : ptr(p) {}

template <class T>
olist<T>::iterator::iterator(const iterator &it) : ptr(it.ptr) {}

template <class T>
bool olist<T>::iterator::operator==(const const_iterator &other) const {
  return ptr == other.ptr;
}

template <class T>
bool olist<T>::iterator::operator!=(const const_iterator &other) const {
  return !(*this == other);
}

template <class T>
typename olist<T>::iterator &olist<T>::iterator::operator++() {
  ptr = ptr->next;
  return *this;
}

template <class T>
typename olist<T>::iterator olist<T>::iterator::operator++(int) {
  ptr = ptr->next;
  return iterator(ptr->prev);
}

template <class T>
typename olist<T>::iterator &olist<T>::iterator::operator--() {
  ptr = ptr->prev;
  return *this;
}

template <class T>
typename olist<T>::iterator olist<T>::iterator::operator--(int) {
  ptr = ptr->prev;
  return iterator(ptr->next);
}

template <class T> const T &olist<T>::iterator::operator*() const {
  return static_cast<node *>(ptr)->obj;
}

template <class T> const T *olist<T>::iterator::operator->() const {
  return &(static_cast<node *>(ptr)->obj);
}

template <class T>
olist<T>::const_iterator::const_iterator(node_base *p) : ptr(p) {}

template <class T>
olist<T>::const_iterator::const_iterator(const const_iterator &cit)
    : ptr(cit.ptr) {}

template <class T>
olist<T>::const_iterator::const_iterator(const iterator &it) : ptr(it.ptr) {}

template <class T>
bool olist<T>::const_iterator::operator==(const const_iterator &other) const {
  return ptr == other.ptr;
}

template <class T>
bool olist<T>::const_iterator::operator!=(const const_iterator &other) const {
  return !(*this == other);
}

template <class T>
typename olist<T>::const_iterator &olist<T>::const_iterator::operator++() {
  ptr = ptr->next;
  return *this;
}

template <class T>
typename olist<T>::const_iterator olist<T>::const_iterator::operator++(int) {
  ptr = ptr->next;
  return const_iterator(ptr->prev);
}

template <class T>
typename olist<T>::const_iterator &olist<T>::const_iterator::operator--() {
  ptr = ptr->prev;
  return *this;
}

template <class T>
typename olist<T>::const_iterator olist<T>::const_iterator::operator--(int) {
  ptr = ptr->prev;
  return const_iterator(ptr->next);
}

template <class T> const T &olist<T>::const_iterator::operator*() const {
  return static_cast<node *>(ptr)->obj;
}

template <class T> const T *olist<T>::const_iterator::operator->() const {
  return &(static_cast<node *>(ptr)->obj);
}

template <class T> olist<T>::olist() : _size(0), pte(new node_base()) {
  pte->prev = pte->next = pte;
}

template <class T>
olist<T>::olist(const olist<T> &other)
    : _size(other._size), pte(new node_base()) {
  pte->prev = pte->next = pte;
  *this = other;
}

template <class T> olist<T>::~olist() {
  clear();
  delete pte;
}

template <class T> const T &olist<T>::front() const { return *begin(); }

template <class T> const T &olist<T>::back() const { return *(--end()); }

template <class T> typename olist<T>::iterator olist<T>::begin() {
  return iterator(pte->next);
}

template <class T> typename olist<T>::const_iterator olist<T>::begin() const {
  return const_iterator(pte->next);
}

template <class T> typename olist<T>::iterator olist<T>::end() {
  return iterator(pte);
}

template <class T> typename olist<T>::const_iterator olist<T>::end() const {
  return const_iterator(pte);
}

template <class T> bool olist<T>::empty() const { return _size == 0; }

template <class T> unsigned int olist<T>::size() const { return _size; }

template <class T> void olist<T>::clear() {
  node_base *p = pte->next;
  while (p != pte) {
    p = p->next;
    delete p->prev;
  }
  pte->prev = pte->next = pte;
  _size = 0;
}

template <class T> typename olist<T>::iterator olist<T>::insert(const T &obj) {
  return insert(obj, end());
}

template <class T>
typename olist<T>::iterator olist<T>::insert(const T &obj, iterator hint) {
  _size++;
  node_base *p = hint.ptr;
  while (p->prev != pte && obj < static_cast<node *>(p->prev)->obj) {
    p = p->prev;
  }
  while (p != pte && static_cast<node *>(p)->obj < obj) {
    p = p->next;
  }
  node *n = new node(obj, p->prev, p);
  n->prev->next = n->next->prev = n;
  return iterator(n);
}

template <class T>
typename olist<T>::iterator olist<T>::insert(const T &obj,
                                             const_iterator hint) {
  _size++;
  node_base *p = hint.ptr;
  while (p->prev != pte && obj < static_cast<node *>(p->prev)->obj) {
    p = p->prev;
  }
  while (p != pte && static_cast<node *>(p)->obj < obj) {
    p = p->next;
  }
  node *n = new node(obj, p->prev, p);
  n->prev->next = n->next->prev = n;
  return iterator(n);
}

template <class T> void olist<T>::erase(iterator pos) {
  _size--;
  pos.ptr->prev->next = pos.ptr->next;
  pos.ptr->next->prev = pos.ptr->prev;
  delete pos.ptr;
}

template <class T> void olist<T>::erase(const_iterator pos) {
  _size--;
  pos.ptr->prev->next = pos.ptr->next;
  pos.ptr->next->prev = pos.ptr->prev;
  delete pos.ptr;
}

template <class T> void olist<T>::pop_back() { erase(--end()); }

template <class T> void olist<T>::pop_front() { erase(begin()); }

template <class T> void olist<T>::merge(olist &other) {
  if (this != &other) {
    _size += other._size;
    other._size = 0;
    node_base *p = pte->next;
    while (other.pte->next != other.pte) {
      while (p != pte && !(static_cast<node *>(other.pte->next)->obj <
                           static_cast<node *>(p)->obj)) {
        p = p->next;
      }
      node_base *o = other.pte->next;
      o->prev->next = o->next;
      o->next->prev = o->prev;
      o->prev = p->prev;
      o->next = p;
      o->prev->next = o->next->prev = o;
    }
  }
}

template <class T> bool olist<T>::contains(const T &obj) const {
  node_base *p = pte->next;
  while (p != pte && !(obj < static_cast<node *>(p)->obj)) {
    if (static_cast<node *>(p)->obj == obj)
      return true;
    p = p->next;
  }
  return false;
}

template <class T> olist<T> &olist<T>::operator=(const olist &other) {
  if (this != &other) {
    clear();
    _size = other._size;
    node_base *p = other.pte->next;
    while (p != other.pte) {
      node *n = new node(static_cast<node *>(p)->obj, pte->prev, pte);
      n->prev->next = n->next->prev = n;
      p = p->next;
    }
  }
  return *this;
}

template <class T> bool olist<T>::operator==(const olist &other) {
  if (this == &other)
    return true;
  if (_size != other._size)
    return false;
  node_base *a = pte->next, *b = other.pte->next;
  while (a != pte) {
    if (!(static_cast<node *>(a)->obj == static_cast<node *>(b)->obj))
      return false;
    a = a->next;
    b = b->next;
  }
  return true;
}

#endif
