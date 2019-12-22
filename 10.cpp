#include <atomic>
#include <chrono>
#include <iostream>
#include <thread>

using namespace std;

atomic<int> thread_counter_started(0);
atomic<int> thread_counter_finished(0);

void execute(void (*fn)(int), int delay) {
    int started_threads = thread_counter_started.load();
    thread_counter_started.store(++started_threads);
    this_thread::sleep_for(chrono::milliseconds(delay));
    (*fn)(started_threads);
    int finished_threads = thread_counter_finished.load();
    thread_counter_finished.store(++finished_threads);
};

int main() {
    void (*function)(int) = [](int thread_count) { cout << "Function executed by thread #" << thread_count << endl; };

    int spawned_threads = 0;
    thread t1(execute, function, 1000); spawned_threads++; t1.detach();
    thread t2(execute, function, 3000); spawned_threads++; t2.detach(); 
    thread t3(execute, function, 2000); spawned_threads++; t3.detach(); 

    int started_threads = thread_counter_started.load();
    int finished_threads = thread_counter_finished.load();
    while (started_threads < spawned_threads || started_threads > finished_threads) {
        started_threads = thread_counter_started.load();
        finished_threads = thread_counter_finished.load();
    }

    cout << "All threads finished" << endl;
}