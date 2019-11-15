#ifndef MONAD_HPP_INCLUDED
#define MONAD_HPP_INCLUDED

#include <memory>
#include <functional>

template <typename A>
class Monad
{
	public:
		virtual std::unique_ptr<A> next(void) = 0;
		virtual bool hasNext(void) = 0;

//		static Unit<A> unit(A element)
//		{
//			return std::make_unique<Monad<A>>(Monad(element));
//		}
//
//		template <typename B>
//		Monad<B> bind(std::function<Monad<B> (A)> func)
//		{
//			return func(m_element);
//		}
//
//		static std::unique_ptr<Monad<A>> mzero(void) { return Monad(); }
//		std::unique_ptr<Monad<A>> mplus(const Monad<A>& other)
//		{
//			Monad<A> temp = this;
//			while (temp.hasNext()) { temp = temp.next(); }
//			temp.m_next = other;
//			return temp;
//		}
//
//	private:
//		A m_element;
};

// abstract base class, only hasNext and next abstract
// subclass zero
// subclass unit, holds item, if item has been accessed
// mplus, holds 2 iterators of the same type, walks throughs first then walks the second
// bind, holds func A->Iterator<B>, saves iterator<B>
//			func(A) then walk over all of the result, then repeat until out of A

#endif
