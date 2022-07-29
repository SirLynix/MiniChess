#pragma once

template<typename T>
class MovablePtr
{
	public:
		MovablePtr(T* ptr = nullptr) :
		m_ptr(ptr)
		{
		}

		MovablePtr(const MovablePtr&) = delete;

		MovablePtr(MovablePtr&& ptr) noexcept :
		m_ptr(ptr)
		{
			ptr.m_ptr = nullptr;
		}

		~MovablePtr() = default;

		T* Get()
		{
			return m_ptr;
		}

		const T* Get() const
		{
			return m_ptr;
		}

		operator T*()
		{
			return m_ptr;
		}

		operator const T*() const
		{
			return m_ptr;
		}

		T* operator->()
		{
			return m_ptr;
		}

		const T* operator->() const
		{
			return m_ptr;
		}

		MovablePtr& operator=(MovablePtr&& ptr) noexcept
		{
			using std::swap;
			swap(m_ptr, ptr.m_ptr);

			return *this;
		}

	private:
		T* m_ptr;
};