#ifndef UNIT_HPP_INCLUDED
#define UNIT_HPP_INCLUDED

#include <memory>
#include "Monad.hpp"

template <typename A>
class Unit : public Monad<A>
{
	public:
		Unit(A item) : m_item(std::make_unique<A>(item)) { }
		Unit(std::unique_ptr<A> item) : m_item(std::move(item)) { }

		std::unique_ptr<A> next(void) { return nullptr; }
		bool hasNext(void) { return false; }
		std::unique_ptr<A> get(void) { return m_item.release(); }
		bool hasItem(void) { return m_item == nullptr; }
	
	private:
		std::unique_ptr<A> m_item;
};

#endif
