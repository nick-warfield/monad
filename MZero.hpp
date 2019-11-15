#ifndef MZERO_HPP_INCLUDED
#define MZERO_HPP_INCLUDED

#include <memory>
#include "Monad.hpp"

template <typename A>
class MZero : public Monad<A>
{
	public:
		std::unique_ptr<A> next(void) { return nullptr; }
		bool hasNext(void) { return false; }
};

#endif
