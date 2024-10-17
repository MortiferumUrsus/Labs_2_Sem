#include <memory>
#include <chrono>
#include <iostream>

struct TestObject {
    int data[100]; // Размер объекта можно менять для тестирования
};

// Функция для измерения времени создания std::shared_ptr
double test_creation(int iterations) {
    using namespace std::chrono;
    auto start = high_resolution_clock::now();
    for(int i = 0; i < iterations; ++i){
        std::shared_ptr<TestObject> ptr = std::make_shared<TestObject>();
    }
    auto end = high_resolution_clock::now();
    duration<double> duration_sec = end - start;
    return duration_sec.count();
}

// Функция для измерения времени копирования std::shared_ptr
double test_copy(int iterations) {
    using namespace std::chrono;
    std::shared_ptr<TestObject> original = std::make_shared<TestObject>();
    auto start = high_resolution_clock::now();
    for(int i = 0; i < iterations; ++i){
        std::shared_ptr<TestObject> copy = original;
    }
    auto end = high_resolution_clock::now();
    duration<double> duration_sec = end - start;
    return duration_sec.count();
}

// Функция для измерения времени присваивания std::shared_ptr
double test_assignment(int iterations) {
    using namespace std::chrono;
    std::shared_ptr<TestObject> target;
    std::shared_ptr<TestObject> source = std::make_shared<TestObject>();
    auto start = high_resolution_clock::now();
    for(int i = 0; i < iterations; ++i){
        target = source;
    }
    auto end = high_resolution_clock::now();
    duration<double> duration_sec = end - start;
    return duration_sec.count();
}

// Функция для измерения времени разыменования std::shared_ptr
double test_dereference(int iterations) {
    using namespace std::chrono;
    std::shared_ptr<TestObject> ptr = std::make_shared<TestObject>();
    volatile int value; // volatile предотвращает оптимизацию
    auto start = high_resolution_clock::now();
    for(int i = 0; i < iterations; ++i){
        value = ptr->data[0];
    }
    auto end = high_resolution_clock::now();
    duration<double> duration_sec = end - start;
    // Использование переменной value предотвращает оптимизацию
    return duration_sec.count();
}

void run_stl_tests() {
    const int iterations = 1000000; // Количество итераций для тестов

    // Тест создания std::shared_ptr
    double creation_time_std = test_creation(iterations);
    std::cout << "Borntime: " << iterations << " std::shared_ptr: " << creation_time_std << " sec\n";

    // Тест копирования std::shared_ptr
    double copy_time_std = test_copy(iterations);
    std::cout << "Copy time: " << iterations << " std::shared_ptr: " << copy_time_std << " sec\n";

    // Тест присваивания std::shared_ptr
    double assignment_time_std = test_assignment(iterations);
    std::cout << "Assigment time: " << iterations << " std::shared_ptr: " << assignment_time_std << " sec\n";

    // Тест разыменования std::shared_ptr
    double dereference_time_std = test_dereference(iterations);
    std::cout << "Dereference time: " << iterations << " std::shared_ptr: " << dereference_time_std << " sec\n";
}