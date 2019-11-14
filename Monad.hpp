#ifndef MONAD_HPP_INCLUDED
#define MONAD_HPP_INCLUDED

#include <iterator>
#include <functional>

template <typename A>
class Monad
{
	public:
		template <typename T>
		using iterator = std::iterator<std::forward_iterator_tag, T>;

		iterator<A> mzero(void);
		iterator<A> unit(A);
		A next();
		bool hasNext(void);

		iterator<A> append(iterator<A> other);
		template <typename B>
		iterator<B> bind(std::function<iterator<B>(A)>);
};

#endif
