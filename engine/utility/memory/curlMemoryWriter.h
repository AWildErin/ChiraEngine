#pragma once

#include <utility>

namespace chira {
    struct CurlMemoryWriter {
        CurlMemoryWriter();
        ~CurlMemoryWriter();
        static void* w_realloc(void* ptr, std::size_t size);
        std::size_t writeMemoryCallback(const char* ptr, std::size_t size, std::size_t nmemb);

        // The following variables are publicly accessed in InternetResourceProvider
        unsigned char* m_pBuffer;
        std::size_t m_Size;
    };
}