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
    : useCount_(1)
    {
    }

    virtual ~SPCountedBase()
    {
    }

    virtual void dispose() = 0;

    void addRef()
    {
        ++useCount_;
    }

    void release()
    {
        if (--useCount_ == 0)
        {
            dispose();
            delete this;
        }
    }

private:
    SPCountedBase(const SPCountedBase& other);
    SPCountedBase& operator=(const SPCountedBase& other);

    volatile long useCount_;
};

template <class X>
class SPCountedImpl : public SPCountedBase
{
public:
    explicit SPCountedImpl(X* px) : px_(px)
    {
    }

    virtual void dispose()
    {
        typedef char type_must_be_complete[sizeof(X) ? 1 : -1];
        (void) sizeof(type_must_be_complete);
        delete px_;
    }

private:
    X* px_;
};

template <class T>
class SharedPtr
{
public:
    typedef T ValueType;

    SharedPtr()
    : px_(0), pn_(0)
    {
    }

    template <class Y>
    explicit SharedPtr(Y* p)
    {
        if (p == 0)
        {
            pn_ = 0;
            px_ = 0;
        }
        else
        {
            pn_ = new ::SPCountedImpl<Y>(p);
            if (pn_)
            {
                px_ = p;
            }
            else
            {
                typedef char type_must_be_complete[sizeof(T) ? 1 : -1];
                (void) sizeof(type_must_be_complete);
                delete p;
                px_ = 0;
            }
        }
    }

    SharedPtr(const SharedPtr& other)
    : px_(other.px_), pn_(other.pn_)
    {
        if (pn_ != 0)
        {
            pn_->addRef();
        }
    }

    template <class Y>
    SharedPtr(const SharedPtr<Y>& other)
    : px_(other.px_), pn_(other.pn_)
    {
        if (pn_ != 0)
        {
            pn_->addRef();
        }
    }

    ~SharedPtr()
    {
        if (pn_ != 0)
        {
            pn_->release();
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
        assert(p == 0 || p != px_);
        ThisType(p).swap(*this);
    }

    T& operator*() const
    {
        assert(px_ != 0);
        return *px_;
    }

    T* operator->() const
    {
        assert(px_ != 0);
        return px_;
    }

    T* get() const
    {
        return px_;
    }

    typedef void (*unspecified_bool_type)();
    static void unspecified_bool_true() {}

    operator unspecified_bool_type() const
    {
        return (px_ == 0) ? 0 : unspecified_bool_true;
    }

    bool operator!() const
    {
        return (px_ == 0);
    }

    void swap(SharedPtr& other)
    {
        std::swap(px_, other.px_);
        std::swap(pn_, other.pn_);
    }

private:
    template <class Y>
    friend class SharedPtr;

    typedef SharedPtr<T> ThisType;

    T* px_;
    ::SPCountedBase* pn_;
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
