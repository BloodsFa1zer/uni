#include <iostream>
#include <string>
#include <thread>
#include <mach/mach.h>

size_t get_current_virtual_memory() {
    mach_task_basic_info info;
    mach_msg_type_number_t count = MACH_TASK_BASIC_INFO_COUNT;
    if (task_info(mach_task_self(), MACH_TASK_BASIC_INFO, (task_info_t)&info, &count) != KERN_SUCCESS) {
        return 0;
    }
    return info.virtual_size;
}

size_t get_current_physical_memory() {
    mach_task_basic_info info;
    mach_msg_type_number_t count = MACH_TASK_BASIC_INFO_COUNT;
    if (task_info(mach_task_self(), MACH_TASK_BASIC_INFO, (task_info_t)&info, &count) != KERN_SUCCESS) {
        return 0;
    }
    return info.resident_size;
}

inline long long memory_difference(size_t start, size_t end) {
    if (end >= start) {
        return end - start;
    } else {
        return (-1) * (start - end);
    }
}

struct BenchmarkMax {
    size_t start_virtual_memory;
    size_t start_physical_memory;
    std::string name;
    size_t max_virtual_memory;
    size_t max_physical_memory;
    bool is_running;
    std::thread measurement_thread;

    BenchmarkMax(std::string name)
            : start_virtual_memory(get_current_virtual_memory()),
              start_physical_memory(get_current_physical_memory()),
              name(name),
              max_virtual_memory(0),
              max_physical_memory(0),
              is_running(true),
              measurement_thread(&BenchmarkMax::run, this) {}

    void measure() {
        size_t current_virtual_memory = get_current_virtual_memory();
        if (current_virtual_memory > max_virtual_memory) {
            max_virtual_memory = current_virtual_memory;
        }

        size_t current_physical_memory = get_current_physical_memory();
        if (current_physical_memory > max_physical_memory) {
            max_physical_memory = current_physical_memory;
        }
    }

    void run() {
        do {
            measure();
            std::this_thread::sleep_for(std::chrono::milliseconds(100)); // avoid busy-waiting
        } while (is_running); // need to run measure at least once
    }

    ~BenchmarkMax() {
        is_running = false;
        measurement_thread.join();

        std::cout << "BenchmarkMax " << name << ": virtual " << memory_difference(start_virtual_memory, max_virtual_memory) <<
                  " bytes, physical " << memory_difference(start_physical_memory, max_physical_memory) << " bytes" << std::endl;
    }
};

