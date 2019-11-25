#ifndef MIMI_HPP_INCLUDED
#define MIMI_HPP_INCLUDED

#include <iterator>
#include <functional>
#include <memory>

namespace mimi
{
	template <typename A>
	class iterator : public std::iterator<std::forward_iterator_tag, A>
	{
		public:
			virtual std::unique_ptr<A> next(void) = 0;
			virtual bool hasNext(void) = 0;
	};

	template <typename A>
	class mzero : public iterator<A>
	{
		public:
			std::unique_ptr<A> next(void) { return nullptr; }
			bool hasNext(void) { return false; }
	};

	template <typename A>
	class unit : public iterator<A>
	{
		public:
			unit(A item) : m_item(std::make_unique<A>(item)) { }
			std::unique_ptr<A> next(void) { return m_item.release(); }
			bool hasNext(void) { return m_item; }

		private:
			std::unique_ptr<A> m_item;
	};

	template <typename A, typename B>
	class bind : public iterator<A>
	{
		public:
			bind(std::unique_ptr<iterator<A>> a,
					std::function<std::unique_ptr<iterator<B>> (A)> f) :
				m_a(std::move(a)),
				m_f(f)
			{
				m_b = std::make_unique<iterator<B>>
					(m_a->hasNext() ? m_f( *(m_a->next()) ) : mzero<B>());
			}

			std::unique_ptr<A> next(void)
			{
				if (m_b->hasNext()) { return m_b->next(); }
				if (m_a->hasNext()) { m_b = m_f( *(m_a->next()) ); }
				return m_b->next();
			}
			bool hasNext(void) { return m_a->hasNext() && m_b->hasNext(); }

		private:
			std::unique_ptr<iterator<A>> m_a;
			std::unique_ptr<iterator<B>> m_b;
			std::function<std::unique_ptr<iterator<B>> (A)> m_f;
	};

	template <typename A>
	class mplus : public iterator<A>
	{
		public:
			mplus(std::unique_ptr<iterator<A>> a, std::unique_ptr<iterator<A>> b) :
				m_a(std::move(a)), m_b(std::move(b)) { }

			std::unique_ptr<A> next(void)
			{
				if (m_a->hasNext()) { return m_a->next(); }
				else if (m_b->hasNext()) { return m_b->next(); }
				else { return nullptr; }
			}
			bool hasNext(void) { return m_a->hasNext() || m_b->hasNext(); }

		private:
			std::unique_ptr<iterator<A>> m_a, m_b;
	};
};

#endif
