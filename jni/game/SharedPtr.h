#ifndef _SHAREDPTR_H_
#define _SHAREDPTR_H_

#include "Types.h"
#include <memory>
#include <algorithm>
#include <assert.h>

class SPCountedBase
{
public:
    SPCountedBase()
    : m_use_count(1)
    {
    }

    virtual ~SPCountedBase()
    {
    }

    virtual void dispose() = 0;

    void addRef()
    {
        ++m_use_count;
    }

    void release()
    {
        if (--m_use_count == 0)
        {
            dispose();
            delete this;
        }
    }

private:
    SPCountedBase(const SPCountedBase& other);
    SPCountedBase& operator=(const SPCountedBase& other);

    volatile long m_use_count;
};

template <class X>
class SPCountedImpl : public SPCountedBase
{
public:
    explicit SPCountedImpl(X* px) : m_px(px)
    {
    }

    virtual void dispose()
    {
        typedef char type_must_be_complete[sizeof(X) ? 1 : -1];
        (void) sizeof(type_must_be_complete);
        delete m_px;
    }

private:
    X* m_px;
};

template <class T>
class SharedPtr
{
public:
    typedef T ValueType;

    SharedPtr()
    : m_px(0), m_pn(0)
    {
    }

    template <class Y>
    explicit SharedPtr(Y* p)
    {
        if (p == 0)
        {
            m_pn = 0;
            m_px = 0;
        }
        else
        {
            m_pn = new ::SPCountedImpl<Y>(p);
            if (m_pn)
            {
                m_px = p;
            }
            else
            {
                typedef char type_must_be_complete[sizeof(T) ? 1 : -1];
                (void) sizeof(type_must_be_complete);
                delete p;
                m_px = 0;
            }
        }
    }

    SharedPtr(const SharedPtr& other)
    : m_px(other.m_px), m_pn(other.m_pn)
    {
        if (m_pn != 0)
        {
            m_pn->addRef();
        }
    }

    template <class Y>
    SharedPtr(const SharedPtr<Y>& other)
    : m_px(other.m_px), m_pn(other.m_pn)
    {
        if (m_pn != 0)
        {
            m_pn->addRef();
        }
    }

    ~SharedPtr()
    {
        if (m_pn != 0)
        {
            m_pn->release();
        }
    }

    SharedPtr& operator=(const SharedPtr& other)
    {
        ThisType(other).swap(*this);
        return *this;
    }

    template <class Y>
    SharedPtr& operator=(const SharedPtr<Y>& other)
    {
        ThisType(other).swap(*this);
        return *this;
    }

    void reset()
    {
        ThisType().swap(*this);
    }

    template <class Y>
    void reset(Y* p)
    {
        assert(p == 0 || p != m_px);
        ThisType(p).swap(*this);
    }

    T& operator*() const
    {
        assert(m_px != 0);
        return *m_px;
    }

    T* operator->() const
    {
        assert(m_px != 0);
        return m_px;
    }

    T* get() const
    {
        return m_px;
    }

    typedef void (*unspecified_bool_type)();
    static void unspecified_bool_true() {}

    operator unspecified_bool_type() const
    {
        return (m_px == 0) ? 0 : unspecified_bool_true;
    }

    bool operator!() const
    {
        return (m_px == 0);
    }

    void swap(SharedPtr& other)
    {
        std::swap(m_px, other.m_px);
        std::swap(m_pn, other.m_pn);
    }

private:
    template <class Y>
    friend class SharedPtr;

    typedef SharedPtr<T> ThisType;

    T* m_px;
    ::SPCountedBase* m_pn;
};

template <class T, class U>
inline bool operator==(const SharedPtr<T>& lhs, const SharedPtr<U>& rhs)
{
    return (lhs.get() == rhs.get());
}

template <class T, class U>
inline bool operator!=(const SharedPtr<T>& lhs, const SharedPtr<U>& rhs)
{
    return (lhs.get() != rhs.get());
}

template <class T>
inline bool operator<(const SharedPtr<T>& lhs, const SharedPtr<T>& rhs)
{
    return (lhs.get() < rhs.get());
}

template <class T>
inline bool operator<=(const SharedPtr<T>& lhs, const SharedPtr<T>& rhs)
{
    return (lhs.get() <= rhs.get());
}

template <class T>
inline bool operator>(const SharedPtr<T>& lhs, const SharedPtr<T>& rhs)
{
    return (lhs.get() > rhs.get());
}

template <class T>
inline bool operator>=(const SharedPtr<T>& lhs, const SharedPtr<T>& rhs)
{
    return (lhs.get() >= rhs.get());
}

#endif
