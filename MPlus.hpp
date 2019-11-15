#ifndef MPLUS_HPP_INCLUDED
#define MPLUS_HPP_INCLUDED

#include <typeinfo>
#include <memory>
#include <type_traits>

#include "Monad.hpp"
#include "MZero.hpp"

template <typename A>
class MPlus : public Monad<A>
{
	public:
		MPlus(A item, std::unique_ptr<Monad<A>> it1, std::unique_ptr<Monad<A>> it2) :
			m_item(std::make_unique<A>(item)),
			m_next1(std::move(it1)),
			m_next2(std::move(it2))
		{ }

		std::unique_ptr<A> next(void);
		bool hasNext(void)
		{
			auto zero = typeid(MZero<A>).hash_code();
			return typeid(*m_next1).hash_code() == zero &&
				typeid(*m_next2).hash_code() == zero;
		}

	private:
		std::unique_ptr<A> m_item;
		std::unique_ptr<Monad<A>> m_next1, m_next2;
};

#endif
