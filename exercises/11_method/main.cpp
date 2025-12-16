#include "../exercise.h"

struct Fibonacci {
    unsigned long long cache[128];
    int cached;

    unsigned long long get(int i) {
        if (i < cached) {
            return this->cache[i];
        }
        for (; (unsigned long long) this->cached < sizeof(this->cache) / sizeof(long long); ++this->cached) {
            this->cache[this->cached] = this->cache[this->cached - 1] + this->cache[this->cached - 2];
        }
        return this->cache[i];
    }
};

int main(int argc, char **argv) {
    Fibonacci fib = {.cache{0, 1}, .cached = 2};
    ASSERT(fib.get(10) == 55, "fibonacci(10) should be 55");
    std::cout << "fibonacci(10) = " << fib.get(10) << std::endl;
    return 0;
}
