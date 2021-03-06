
#pragma once
#ifndef TOMATO_VECTOR_HPP_
    #define TOMATO_VECTOR_HPP_

    #include "core.hpp"

namespace tom
{

// --------------------------------------------------------------------------------------------
/// Simple custom vector class that stores data on the heap
// --------------------------------------------------------------------------------------------
template<typename T>
class vector
{
public:
    vector()
    {
        _capacity = 2;
        _size     = 0;
        _data     = malloc(sizeof(T) * _capacity);
    }
    ~vector() { free(_data); }

    // TODO: implement  copy/move constructors
    vector(const vector &other)
    {
        _capacity = 2;
        _size     = 0;
        _data     = malloc(sizeof(T) * _capacity);
        resize(other.size());
        memcpy(_data, other.data(), sizeof(T) * _size);
    }
    vector &operator=(const vector &lhs)
    {
        _capacity = 2;
        _size     = 0;
        _data     = malloc(sizeof(T) * _capacity);
        resize(lhs.size());
        memcpy(_data, lhs.data(), sizeof(T) * _size);
    }
    vector(vector &&) = delete;
    vector &operator=(vector &&) = delete;

    void push_back(const T &item)
    {
        if (_size >= _capacity) {
            grow();
        }
        reinterpret_cast<T *>(_data)[_size++] = item;
    }

    void pop_back()
    {
        if (_size != 0) reinterpret_cast<T *>(_data)[--_size].~T();
    }

    template<class... Args>
    void emplace_back(Args const &...args)
    {
        if (_size >= _capacity) {
            grow();
        }
        T *loc = &(reinterpret_cast<T *>(_data)[_size++]);
        new (loc) T(args...);
    }

    void resize(size_t new_size)
    {
        if (new_size > _capacity) {
            grow(new_size);
        }

        if (new_size < _size) {
            auto data_ptr = reinterpret_cast<T *>(_data);
            for (szt i = new_size; i < _size; ++i) {
                data_ptr[i].~T();
            }
        }

        _size = new_size;
    }

    void clear()
    {
        auto data_ptr = reinterpret_cast<T *>(_data);
        for (szt i = 0; i < _size; ++i) {
            data_ptr[i].~T();
        }
        _size = 0;
    }

    szt size() const { return _size; }
    szt capacity() const { return _capacity; }
    bool empty() const { return _size == 0; }
    void *data() { return (void *)_data; }
    void *data() const { return (void *)_data; }

    T *begin() { return reinterpret_cast<T *>(_data); }
    T *end() { return reinterpret_cast<T *>(_data) + _size; }
    T const *begin() const { return reinterpret_cast<T *>(_data); }
    T const *end() const { return reinterpret_cast<T *>(_data) + _size; }

    T &operator[](szt i)
    {
        TOM_ASSERT(i < _size);
        return reinterpret_cast<T *>(_data)[i];
    }

    T const &operator[](szt i) const
    {
        TOM_ASSERT(i < _size);
        return reinterpret_cast<T *>(_data)[i];
    }

private:
    void grow()
    {
        // TODO: option to use game memory block?
        // TODO:  better grow algorithm?
        szt new_capacity = _capacity * 2;

        void *old_storage = _data;
        void *new_storage = malloc(sizeof(T) * new_capacity);
        memcpy(new_storage, old_storage, _size * sizeof(T));

        _data     = new_storage;
        _capacity = new_capacity;

        free(old_storage);
    }

    void grow(szt new_capacity)
    {
        if (new_capacity > _capacity) {
            void *old_storage = _data;
            void *new_storage = malloc(sizeof(T) * new_capacity);
            memcpy(new_storage, old_storage, _size * sizeof(T));

            _data     = new_storage;
            _capacity = new_capacity;

            free(old_storage);
        }
    }

    void *_data;
    szt _size;
    szt _capacity;
};

// --------------------------------------------------------------------------------------------
/// Reduces heap allocations when list is shorter. It uses a small array for a dedicated size.
/// When the growing gets bigger than this small cache a dynamic growing algorithm will be
/// used.
// --------------------------------------------------------------------------------------------
template<typename T, szt Capacity>
class small_vector
{
public:
    small_vector() : _storage(_inplace_storage), _size(0), _capacity(Capacity) {}

    ~small_vector()
    {
        if (_storage != _inplace_storage) {
            delete[] _storage;
        }
    }

    small_vector(const small_vector &) = delete;
    small_vector(small_vector &&)      = delete;
    small_vector &operator=(const small_vector &) = delete;
    small_vector &operator=(small_vector &&) = delete;

    void push_back(const T &item)
    {
        if (_size < _capacity) {
            _storage[_size++] = item;
            return;
        }

        push_back_and_grow(item);
    }

    void resize(size_t new_size)
    {
        if (new_size > _capacity) {
            grow(new_size);
        }
        _size = new_size;
    }

    szt size() const { return _size; }
    T *data() { return _storage; }

    T *begin() { return _storage; }
    T *end() { return &_storage[_size]; }
    T *begin() const { return _storage; }
    T *end() const { return &_storage[_size]; }

    T &operator[](szt i)
    {
        TOM_ASSERT(i < _size);
        return _storage[i];
    }
    T const &operator[](szt i) const
    {
        TOM_ASSERT(i < _size);
        return _storage[i];
    }

private:
    void grow(szt new_capacity)
    {
        T *old_storage = _storage;
        T *new_storage = new T[new_capacity];

        // TODO: option to use game memory block?
        memcpy(new_storage, old_storage, _size * sizeof(T));

        _storage  = new_storage;
        _capacity = new_capacity;

        if (old_storage != _inplace_storage) {
            delete[] old_storage;
        }
    }

    void push_back_and_grow(const T &item)
    {
        grow(_capacity + Capacity);

        _storage[_size++] = item;
    }

    T *_storage;
    szt _size;
    szt _capacity;
    T _inplace_storage[Capacity];
};

// --------------------------------------------------------------------------------------------
/// C-array wrapper
// --------------------------------------------------------------------------------------------

template<typename T, szt Size>
class array
{
public:
    array() { _size = Size; }
    ~array() {}

    // TODO: implement  copy/move constructors
    array(const array &) = delete;
    array(array &&)      = delete;
    array &operator=(const array &) = delete;
    array &operator=(array &&) = delete;

    // just does a placement new
    template<class... Args>
    void emplace_at(szt i, Args const &...args)
    {
        TOM_ASSERT(i < _size);
        if (i > _size) return;
        new (&_data[i]) T(args...);
    }

    szt size() const { return _size; }
    T *data() { return _data; }

    T *begin() { return _data; }
    T *end() { return _data + _size; }
    T const *begin() const { return _data; }
    T const *end() const { return _data + _size; }

    T &operator[](szt i)
    {
        TOM_ASSERT(i < _size);
        return _data[i];
    }

    T const &operator[](szt i) const
    {
        TOM_ASSERT(i < _size);
        return _data[i];
    }

private:
    T _data[Size];
    szt _size;
};

}  // namespace tom

#endif
