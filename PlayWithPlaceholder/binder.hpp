#ifndef BINDER_HPP
#define BINDER_HPP

template<int I> class placeholder{};
placeholder<1> _1;
placeholder<2> _2;
placeholder<3> _3;

template<typename A1> class list1
{
    A1 a1_;
public:
    list1(A1 a1): a1_(a1){}
    A1 operator[](placeholder<1>) const { return a1_; }
    template<typename T> T operator[](T v) const { return v; }
};

template<typename A1, typename A2, typename A3> class list3
{
    A1 a1_;A2 a2_;A3 a3_;
public:
    list3(A1 a1, A2 a2, A3 a3): a1_(a1),a2_(a2),a3_(a3){}
    template<typename T> T operator[](T v) const { return v; }
    template<typename F, typename List1> void operator()(F f, List1 list1)   {
        f(list1[a1_], list1[a2_], list1[a3_]);
    }
};

template<typename F, typename List> class binder
{
    F f_;
    List  list_;
public:
    binder(F f, List  list):f_(f), list_(list){}
    template<typename A> void operator()(A a)   {
        list1<A> lst(a); // Explanation coming
        list_(f_, lst);
    }
};

template<typename F, typename A1, typename A2, typename A3>
binder<F, list3<A1, A2, A3> > bind(F f, A1 a1, A2 a2, A3 a3)
{
  typedef  list3<A1, A2, A3> list_type;
  list_type  list(a1, a2, a3);
  return binder<F, list_type>(f, list);
}

#ifdef REMINDER
template<typename InIt, typename UnaryFn>
Fn for_each(InIt first, InIt last, UnaryFn fn) {
  for(; first != last; ++first)
      fn(*first);
  return fn;
}
#endif //REMINDER

#endif // BINDER_HPP
