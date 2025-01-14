// This file is a part of Akel
// Authors : @kbz_8
// Created : 09/09/2021
// Updated : 30/03/2022

#ifndef __AK_UNIQUE_PTR_WRAPPER__
#define __AK_UNIQUE_PTR_WRAPPER__

#include <Akpch.h>
#include <Core/core.h>

namespace Ak
{
    /**
     * Using a struct as a deleter requires as much memory as using a lambda expression (without std::function).
     * Because of this, the unique_ptr has the same size as a raw pointer (8 bytes for 64-bit systems)
     */
    template <typename T>
    struct unique_ptr_w_deleter
    {
        void operator()(T* ptr)
        {
            if(ptr == nullptr)
                return;
            void* address = ptr;
            memFree(ptr);

		    if(Core::ProjectFile::getBoolValue("unique_ptr_wrapper_enable_debug_message"))
                Core::log::report(MESSAGE, "unique_ptr_w : pointer freed %p", address);

            address = nullptr;
        }
    };

    template <typename T>
    using unique_ptr_w = std::unique_ptr<T, unique_ptr_w_deleter<T>>;

    template <typename T>
    inline unique_ptr_w<T> make_unique_ptr_w(T* ptr) noexcept { return unique_ptr_w<T>(ptr); }

    template <typename T = void, typename ... Args>
    inline unique_ptr_w<T> create_unique_ptr_w(Args&& ... args) noexcept { return make_unique_ptr_w<T>(memAlloc<T>(std::forward<Args>(args)...)); }
}

#endif // __AK_UNIQUE_PTR_WRAPPER__
