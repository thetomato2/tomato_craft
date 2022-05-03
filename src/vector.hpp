
/**  Defines small vector with inplace storage.
Based on CppCon 2016: Chandler Carruth "High Performance Code 201: Hybrid Data Structures" */

#ifndef TOMATO_SMALLVECTOR_HPP_
#define TOMATO_SMALLVECTOR_HPP_

#include "common.hpp"

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
        s32 x = 0;
    }
    ~vector() { delete[] _data; }

    // TODO: implement  copy/move constructors
    vector(const vector &) = delete;
    vector(vector &&)      = delete;
    vector &operator=(const vector &) = delete;
    vector &operator=(vector &&) = delete;

    void push_back(const T &item)
    {
        if (_size >= _capacity) {
            grow();
        }
        reinterpret_cast<T *>(_data)[_size++] = item;
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
        _size = new_size;
    }

    szt size() const { return _size; }
    szt capacity() const { return _capacity; }
    void *data() { return (void *)_data; }

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
        szt new_capacity = _capacity * 2;

        void *old_storage = _data;
        void *new_storage = malloc(sizeof(T) * new_capacity);
        memcpy(new_storage, old_storage, _size * sizeof(T));

        _data     = new_storage;
        _capacity = new_capacity;

        free(old_storage);
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
template<typename T, u32 Capacity>
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

}  // namespace tom

#endif
