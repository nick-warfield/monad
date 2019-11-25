#ifndef MIMI_HPP_INCLUDED
#define MIMI_HPP_INCLUDED

#include <functional>
#include <memory>
#include <optional>

namespace mimi
{
	template <typename A>
	class iterator
	{
		public:
			virtual ~iterator(void);
			virtual std::optional<A> next(void) = 0;
			virtual bool hasNext(void) = 0;
	};

	template <typename A>
	class mzero : public iterator<A>
	{
		public:
			std::optional<A> next(void) { return std::nullopt; }
			bool hasNext(void) { return false; }
	};

	template <typename A>
	class unit : public iterator<A>
	{
		public:
			unit(A item) : m_item(item) { }
			std::optional<A> next(void)
			{
				auto value = m_item;
				m_item.reset();
				return value;
			}
			bool hasNext(void) { return (bool)m_item; }

		private:
			std::optional<A> m_item;
	};

	template <typename A, typename B>
	class bind : public iterator<A>
	{
		public:
			bind(iterator<A>& a,
					std::function<std::unique_ptr<iterator<B>> (A)> f) :
				m_a(std::make_unique<iterator<A>>(a)),
				m_func(f)
			{
			}

			std::optional<A> next(void)
			{
				if (m_b->hasNext()) { return m_b->next(); }
				if (m_a->hasNext()) { m_b = m_f( m_a->next() ); }
				return m_b->next();
			}
			bool hasNext(void) { return m_a.hasNext() && m_b.hasNext(); }

		private:
			std::unique_ptr<iterator<A>> m_a;
			std::unique_ptr<iterator<B>> m_b;
			std::function<std::unique_ptr<iterator<B>> (A)> m_func;
	};

	template <typename A>
	class mplus : public iterator<A>
	{
		public:
			mplus(iterator<A>& a, iterator<A>& b) :
				m_a(std::make_unique<iterator<A>>(a)),
				m_b(std::make_unique<iterator<A>>(b))
			{ }

			std::optional<A> next(void)
			{
				bool aNext = m_a->hasNext();
				auto a = m_a->next();
				auto b = m_b->next();
				return aNext ? a : b;
			}
			bool hasNext(void) { return m_a->hasNext() || m_b->hasNext(); }

		private:
			std::unique_ptr<iterator<A>> m_a, m_b;
	};

	template <typename A>
	auto make_mimi(void)
	{
		return std::make_unique<mzero<A>>();
	}

	template <typename A>
	auto make_mimi(A item)
	{
		return std::make_unique<unit<A>>(item);
	}

	template <typename A, typename B>
	auto make_mimi(
			iterator<A>& a,
			std::function<std::unique_ptr<iterator<B>> (A)> f)
	{
		return std::make_unique<bind<A, B>>(a, f);
	}

	template <typename A>
	auto make_mimi(iterator<A>& a, iterator<A>& b)
	{
		return std::make_unique<mplus<A>>(a, b);
	}
};

#endif
