#ifndef BIND_HPP_INCLUDED
#define BIND_HPP_INCLUDED

#include <memory>
#include <functional>
#include "Monad.hpp"
#include "MZero.hpp"

template <typename A, typename B>
class Bind : public Monad<A>
{
	public:
		Bind(A item, std::function<std::unique_ptr<Monad<B>> (A)> func) :
			m_item(std::make_unique<A>(item)),
			m_func(func),
			m_output(std::make_unique<Monad<B>>(MZero<B>()))
		{ }

		std::unique_ptr<A> next(void);
		bool hasNext(void);

	private:
		std::unique_ptr<A> m_item;
		std::function<std::unique_ptr<Monad<B>> (A)> m_func;
		std::unique_ptr<Monad<B>> m_output;
};

#endif
