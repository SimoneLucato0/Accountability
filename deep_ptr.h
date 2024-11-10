#ifndef UNIQUE_PTR_H
#define UNIQUE_PTR_H

template <class T>
class DeepPtr
{
  T *ptr;

public:
  DeepPtr();
  explicit DeepPtr(T *p);
  DeepPtr(const DeepPtr &o);
  ~DeepPtr();

  T *release();
  void reset(T *p = nullptr);
  void swap(DeepPtr &o);
  T *get() const;

  DeepPtr &operator=(const DeepPtr &o);
  T &operator*() const;
  T *operator->() const;
  operator bool() const;
};

template <class T, class U>
bool operator==(const DeepPtr<T> &l, const DeepPtr<U> &r);
template <class T, class U>
bool operator!=(const DeepPtr<T> &l, const DeepPtr<U> &r);
template <class T, class U>
bool operator<(const DeepPtr<T> &l, const DeepPtr<U> &r);
template <class T, class U>
bool operator>(const DeepPtr<T> &l, const DeepPtr<U> &r);
template <class T, class U>
bool operator<=(const DeepPtr<T> &l, const DeepPtr<U> &r);
template <class T, class U>
bool operator>=(const DeepPtr<T> &l, const DeepPtr<U> &r);

template <class T>
DeepPtr<T>::DeepPtr() : ptr(nullptr) {}

template <class T>
DeepPtr<T>::DeepPtr(T *p) : ptr(p) {}

template <class T>
DeepPtr<T>::DeepPtr(const DeepPtr &o) : ptr(o->clone()) {}

template <class T>
DeepPtr<T>::~DeepPtr()
{
  if (ptr)
    delete ptr;
}

template <class T>
T *DeepPtr<T>::release()
{
  T *old = ptr;
  if (ptr)
    delete ptr;
  return old;
}

template <class T>
void DeepPtr<T>::reset(T *p)
{
  T *old = ptr;
  ptr = p;
  if (old)
    delete old;
}

template <class T>
void DeepPtr<T>::swap(DeepPtr &o)
{
  T *p = ptr;
  ptr = o.ptr;
  o.ptr = p;
}

template <class T>
T *DeepPtr<T>::get() const { return ptr; }

template <class T>
DeepPtr<T> &DeepPtr<T>::operator=(const DeepPtr &o)
{
  if (this != &o)
  {
    if (ptr)
      delete ptr;
    ptr = o->clone();
  }
  return *this;
}

template <class T>
T &DeepPtr<T>::operator*() const { return *get(); }

template <class T>
T *DeepPtr<T>::operator->() const { return get(); }

template <class T, class U>
bool operator==(const DeepPtr<T> &l, const DeepPtr<U> &r)
{
  return l.get() == r.get();
}
template <class T, class U>
bool operator!=(const DeepPtr<T> &l, const DeepPtr<U> &r)
{
  return !(l == r);
}
template <class T, class U>
bool operator<(const DeepPtr<T> &l, const DeepPtr<U> &r)
{
  return r.get() && (!l.get() || *l.get() < *r.get());
}

template <class T, class U>
bool operator>(const DeepPtr<T> &l, const DeepPtr<U> &r)
{
  return r < l;
}

template <class T, class U>
bool operator<=(const DeepPtr<T> &l, const DeepPtr<U> &r)
{
  return !(r < l);
}

template <class T, class U>
bool operator>=(const DeepPtr<T> &l, const DeepPtr<U> &r)
{
  return !(l < r);
}

template <class T>
DeepPtr<T>::operator bool() const { return get(); }

#endif