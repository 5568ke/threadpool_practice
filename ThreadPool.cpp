#include <thread>
#include <iostream>
#include <vector>
#include <functional>
#include <concurrentqueue.h>
#include <future>

class ThreadPool {
public:
    ThreadPool(size_t thread_count) : workers_(thread_count), queues_(thread_count) {
        for (size_t i = 0; i < thread_count; ++i) {
            workers_[i] = std::thread([this, i] { work(i); });
        }
    }

    ~ThreadPool() {
        stop();
    }

    template<typename F, typename... Args>
    void enqueue(F&& f, Args&&... args) {
        auto task = std::make_shared<std::packaged_task<void()>>(std::bind(std::forward<F>(f), std::forward<Args>(args)...));
        auto index = next_queue_.fetch_add(1) % queues_.size();
        queues_[index].enqueue([task]() { (*task)(); });
    }

    void stop() {
        for (auto& queue : queues_) {
            queue.enqueue(nullptr);
        }
        for (auto& worker : workers_) {
            if (worker.joinable()) {
                worker.join();
            }
        }
    }

private:
    using Task = std::function<void()>;

    void work(size_t index) {
        moodycamel::ConsumerToken token(queues_[index]);
        while (true) {
            Task task;
            if (queues_[index].try_dequeue(token, task)) {
                if (!task) {
                    break;
                }
                task();
            }
            else {
                // Steal task from other queues
                for (size_t i = 0; i < queues_.size(); ++i) {
                    if (i != index && queues_[i].try_dequeue(task)) {
                        task();
                        break;
                    }
                }
                // Sleep for a while to avoid spinning
                std::this_thread::yield();
            }
        }
    }

    std::vector<std::thread> workers_;
    std::vector<moodycamel::ConcurrentQueue<Task>> queues_;
    std::atomic<int> next_queue_{ 0 };
};


int main(){
  const int thread_count=std::thread::hardware_concurrency();
  ThreadPool pool(4);
  pool.stop();

}
