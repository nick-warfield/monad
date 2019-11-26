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
			virtual ~iterator(void) { }
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
	class bind : public iterator<B>
	{
		public:
			bind(std::unique_ptr<iterator<A>> a,
					std::function<std::unique_ptr<iterator<B>> (A)> f) :
				m_a(std::move(a)),
				m_b(std::make_unique<mzero<B>>()),
				m_func(f)
			{ }

			std::optional<B> next(void)
			{
				if (m_b->hasNext()) { return m_b->next(); }
				if (m_a->hasNext()) { m_b = m_func( m_a->next().value() ); }
				return m_b->next();
			}
			bool hasNext(void) { return m_a->hasNext() || m_b->hasNext(); }

		private:
			std::unique_ptr<iterator<A>> m_a;
			std::unique_ptr<iterator<B>> m_b;
			std::function<std::unique_ptr<iterator<B>> (A)> m_func;
	};

	template <typename A>
	class mplus : public iterator<A>
	{
		public:
			mplus(std::unique_ptr<iterator<A>> a, std::unique_ptr<iterator<A>> b)
				: m_a(std::move(a)), m_b(std::move(b)) { }

			std::optional<A> next(void)
			{
				return m_a->hasNext() ? m_a->next() : m_b->next();
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
			std::unique_ptr<iterator<A>> a,
			std::function<std::unique_ptr<iterator<B>> (A)> f)
	{
		return std::make_unique<bind<A, B>>(std::move(a), f);
	}

	template <typename A>
	auto make_mimi(std::unique_ptr<iterator<A>> a, std::unique_ptr<iterator<A>> b)
	{
		return std::make_unique<mplus<A>>(std::move(a), std::move(b));
	}
};

#endif
