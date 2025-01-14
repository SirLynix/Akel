// This file is a part of Akel
// Authors : @kbz_8
// Created : 02/08/2021
// Updated : 30/03/2022

#include <Core/Memory/fixedAllocator.h>
#include <Core/log.h>

namespace Ak
{
    template <typename T = void, typename ... Args>
    T* FixedAllocator::alloc(Args&& ... args)
    {
        if(!canAlloc())
        {
            if(_autoResize)
                resize(_bits.size() * 2);
            else
            {
                Core::log::report(ERROR, "Fixed Allocator: unable to alloc block, no more block free");
                return nullptr;
            }
        }

        _mutex.lockThreads();

        *_it = true;

        if(std::is_class<T>::value)
        {
            T* ptr = reinterpret_cast<T*>(reinterpret_cast<uintptr_t>(_heap) + _block_size * (std::distance(_it, _bits.rend()) - 1));
            _mutex.unlockThreads();
            ::new ((void*)ptr) T(std::forward<Args>(args)...);

            return ptr;
        }

        _mutex.unlockThreads();

        return reinterpret_cast<T*>(reinterpret_cast<uintptr_t>(_heap) + _block_size * (std::distance(_it, _bits.rend()) - 1));
    }

    template <typename T = void>
    void FixedAllocator::free(T* ptr)
    {
        if(!contains(ptr))
        {
            Core::log::report(WARNING, "Fixed Allocator: a pointer allocated by another allocator will be freed, this may be an error");
            delete ptr;
            return;
        }

        _mutex.lockThreads();

        if(std::is_class<T>::value)
            ptr->~T();

        const size_t index = (reinterpret_cast<uintptr_t>(ptr) - reinterpret_cast<uintptr_t>(_heap)) / _block_size;
        _bits[index] = false;

        _mutex.unlockThreads();
    }
}
