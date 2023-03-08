#include <thread>
#include <type_traits>
#include <chrono>
#include <string>
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
        // stop();
    }

    template<typename F, typename... Args>
    decltype(auto) enqueue(F&& f, Args&&... args) {
        using return_type = typename std::invoke_result<F,Args...>::type;
        auto task = std::make_shared<std::packaged_task<return_type()>>(std::bind(std::forward<F>(f), std::forward<Args>(args)...));
        std::future<return_type> res = task->get_future(); 

        // add job to per thread job queue
        auto index = next_queue_.fetch_add(1) % queues_.size();
        queues_[index].enqueue([task]() { (*task)(); });
        return res;
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
        // int steal_count = 0;
        while (true) {
            Task task;
            if (queues_[index].try_dequeue(token, task)) {
                if (!task) {
                    break;
                }
                task();
                // steal_count = 0; 
            }
            else {
                
                // job stealing
                // bool stolen = false;
                // for (size_t i = 1; i < queues_.size() && !stolen; ++i) {
                //     Task stolen_task;
                //     if (queues_[(index + i) % queues_.size()].try_dequeue(stolen_task)) {
                //         // steal success -> run
                //          stolen_task();
                //          stolen = true;
                //          steal_count = 0;
                //     }
                // }
                // if (!stolen) {
                //     ++steal_count;
                //     if (steal_count > 1000) { 
                //         // can't steal job -> sleep
                //         std::this_thread::yield();
                //         steal_count = 0; 
                //     }
                // }
                std::this_thread::yield();
            }
        }
    }
    std::vector<std::thread> workers_;
    std::vector<moodycamel::ConcurrentQueue<Task>> queues_;
    std::atomic<int> next_queue_{ 0 };
};


int main(){
  const int max_thread_numbers=std::thread::hardware_concurrency();
  int thread_count,task_size; //=std::thread::hardware_concurrency();
  std::cout<<"cpu support threads number : "<<max_thread_numbers<<std::endl;
  std::cout<<"threads number : ";
  std::cin>>thread_count;
  std::cout<<"task size : ";
  std::cin>>task_size;
  std::cout<<std::endl;

  std::string output_data="";
  ThreadPool pool(thread_count);
  output_data+="==============================================";
  output_data+='\n';
  output_data+=" initialize threadpool with : ";
  output_data+= std::to_string(thread_count);
  output_data+=" threads";
  output_data+='\n';
  output_data+=" task size : ";
  output_data+= std::to_string(task_size);
  output_data+='\n';


  std::vector<std::future<int>> futures(1000000);

    
  std::chrono::steady_clock::time_point t1 = std::chrono::steady_clock::now();
  for(int i=0;i<1000000;i++){
      futures[i]=pool.enqueue([=](){
          int c=0;
          for(int count=0;count<task_size;count++){
            c+=count;
          }
          return c;
      });
  }
  pool.stop();
  std::chrono::steady_clock::time_point t2 = std::chrono::steady_clock::now();
  output_data+=" use time : ";
  output_data+=std::to_string((t2-t1).count());
  output_data+='\n';
  output_data+=" exit";
  output_data+='\n';
  output_data+="==============================================";
  output_data+='\n';
  std::cout<<output_data;
}
