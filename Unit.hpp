#ifndef UNIT_HPP_INCLUDED
#define UNIT_HPP_INCLUDED

#include <memory>
#include "Monad.hpp"

template <typename A>
class Unit : public Monad<A>
{
	public:
		Unit(A item) : m_item(std::make_unique<A>(item)) { }

		std::unique_ptr<A> next(void) { return m_item.release(); }
		bool hasNext(void) { return m_item; }
	
	private:
		std::unique_ptr<A> m_item;
};

#endif
