#ifndef MONAD_HPP_INCLUDED
#define MONAD_HPP_INCLUDED

#include <memory>
#include <functional>

template <typename A>
class Monad
{
	public:
		Monad(A element) : m_element(element), m_next(nullptr) { }

		A next(void) { return hasNext() ? m_next.m_element : nullptr; }
		bool hasNext(void) { return m_next != nullptr; }
		static Monad<A> unit(A element) { return Monad(element); }

		template <typename B>
		Monad<B> bind(std::function<Monad<B> (A)> func)
		{
			return func(m_element);
		}

		static Monad<A> mzero(void) { return Monad(); }
		Monad<A> mplus(Monad<A> other)
		{
			Monad<A> temp = this;
			while (temp.hasNext()) { temp = temp.next(); }
			temp.m_next = other;
			return temp;
		}

	private:
		Monad(void) : m_element(), m_next(nullptr) { }
		A m_element;
		std::unique_ptr<Monad<A>> m_next;
};

// abstract base class, only hasNext and next abstract
// subclass zero
// subclass unit, holds item, if item has been accessed
// mplus, holds 2 iterators of the same type, walks throughs first then walks the second
// bind, holds func A->Iterator<B>, saves iterator<B>
//			func(A) then walk over all of the result, then repeat until out of A

#endif
