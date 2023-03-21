#ifndef ENGINE_UTILS_DEBUG_HPP_
#define ENGINE_UTILS_DEBUG_HPP_

#define CHECK_TRUE(flag)                            \
    {                                               \
        bool value = flag;                          \
        if (value == true) {                        \
            Debug::LogSuccess("CHECK_TRUE " #flag); \
        } else {                                    \
            Debug::LogError("CHECK_TRUE " #flag);   \
        }                                           \
    }

#define CHECK_NULL(ptr)                            \
    {                                              \
        void* value = ptr;                         \
        if (value == nullptr) {                    \
            Debug::LogError("CHECK_NULL " #ptr);   \
        } else {                                   \
            Debug::LogSuccess("CHECK_NULL " #ptr); \
        }                                          \
    }

class Debug {
 public:
    static void Log(const char* message);
    static void LogError(const char* message);
    static void LogSuccess(const char* message);
};

#endif  // ENGINE_UTILS_DEBUG_HPP_
