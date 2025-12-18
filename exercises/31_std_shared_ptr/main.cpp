#include "../exercise.h"
#include <memory>

// READ: `std::shared_ptr` <https://zh.cppreference.com/w/cpp/memory/shared_ptr>
// READ: `std::weak_ptr` <https://zh.cppreference.com/w/cpp/memory/weak_ptr>

int main(int argc, char **argv) {
    auto shared = std::make_shared<int>(10);
    std::shared_ptr<int> ptrs[]{shared, shared, shared};

    std::weak_ptr<int> observer = shared;
    ASSERT(observer.use_count() == 4, "");

    // 重置：使它不再引用shared
    ptrs[0].reset();
    ASSERT(observer.use_count() == 3, "");

    // 重新赋值，不再引用shared
    ptrs[1] = nullptr;
    ASSERT(observer.use_count() == 2, "");

    ptrs[2] = std::make_shared<int>(*shared);
    ASSERT(observer.use_count() == 1, "");

    ptrs[0] = shared;
    ptrs[1] = shared;
    ptrs[2] = std::move(shared);
    ASSERT(observer.use_count() == 3, "");

    std::ignore = std::move(ptrs[0]);
    ptrs[1] = std::move(ptrs[1]);
    ptrs[1] = std::move(ptrs[2]);
    ASSERT(observer.use_count() == 2, "");

    // lock会返回一个共享指针，并使计数+1
    shared = observer.lock();
    ASSERT(observer.use_count() == 3, "");

    shared = nullptr;
    for (auto &ptr : ptrs) ptr = nullptr;
    ASSERT(observer.use_count() == 0, "");

    // 通过lock获取共享指针，但是由于没有其他共享指针引用shared，仍为0
    // 尝试将weak ptr 提升为 shared ptr, 若对象依然存活，返回一个共享指针，并计数+1； 若对象销毁，返回一个空的共享指针（nullptr）
    shared = observer.lock();
    ASSERT(observer.use_count() == 0, "");

    return 0;
}
