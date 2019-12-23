#include <atomic>
#include <chrono>
#include <functional>
#include <iostream>
#include <thread>

using namespace std;

atomic<int> thread_counter_started(0);
atomic<int> thread_counter_finished(0);

void execute(void (*fn)(unsigned int), int delay) {
    int started_threads = thread_counter_started.load();
    thread_counter_started.store(++started_threads);
    this_thread::sleep_for(chrono::milliseconds(delay));
    (*fn)(hash<thread::id>{}(this_thread::get_id()));
    int finished_threads = thread_counter_finished.load();
    thread_counter_finished.store(++finished_threads);
};

int main() {
    void (*function)(unsigned int) = [](unsigned int thread_id) { 
        cout << "Function executed by thread with ID: " << thread_id << endl;
    };

    int spawned_threads = 0;
    thread t1(execute, function, 1000); spawned_threads++; t1.detach();
    thread t2(execute, function, 3000); spawned_threads++; t2.detach(); 
    thread t3(execute, function, 2000); spawned_threads++; t3.detach(); 

    int started_threads = thread_counter_started.load();
    while (started_threads < spawned_threads) { started_threads = thread_counter_started.load(); }
    cout << "All threads started" << endl;
    
    int finished_threads = thread_counter_finished.load();
    while (started_threads > finished_threads) { finished_threads = thread_counter_finished.load(); }
    cout << "All threads finished" << endl;
}