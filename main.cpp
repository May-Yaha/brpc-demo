#include <iostream>
#include <mutex>
#include <chrono>
#include <thread>
#include <boost/thread/thread.hpp>

using namespace std;

// 用于防止多个线程抢占终端输出导致输出混乱的锁
mutex log_mt;

// 具体的元素
class Stone {
 public:
  float weight;

  ~Stone() {}

  Stone() {
    weight = rand() % 100;
  }
};


// 缓冲类
class Busket {
 private:
  deque<Stone> dq;
 public:
  mutex mt;

  bool empty() const {
    return dq.empty();
  }

  const Stone get() {
    Stone temp = *(dq.begin());
    dq.erase(dq.begin());
    return temp;
  }

  void add() {
    dq.emplace_back(Stone());
  }

  const unsigned int size() {
    return dq.size();
  }
};


// 生产者类
class Provider {
 private:
  int aim_num;
  Busket* pbusket;

 public:
  ~Provider() {}

  Provider(const int num, Busket& busket)
      : aim_num(num), pbusket(&busket) {}

  void build_stone() {
    const int NUM_TO_BUILD = rand() % 20;
    int ct = 0;

    while (pbusket->size() < aim_num && ct < NUM_TO_BUILD) {
      ++ct;
      lock_guard<mutex> lg(pbusket->mt);
      pbusket->add();
    }
  }
};


// 消费者类
class Custmer {
 private:
  Busket* pbusket;

 public:
  ~Custmer() {
    pbusket = nullptr;
  }

  Custmer(Busket& busket)
      : pbusket(&busket) {}

  const Stone get() const {
    lock_guard<mutex> lg(pbusket->mt);
    cout << "NUM IN BUSKET NOW IS : " << pbusket->size() << endl;
    return pbusket->get();
  }

  bool can_take() const {
    return !pbusket->empty();
  }
};


// 生产者子函数
void func_provider(Provider& provider) {
  while (1) {
    this_thread::sleep_for(chrono::seconds(1));
    provider.build_stone();
  }
}


// 消费者子函数
void func_custmer(Custmer& custmer) {
  while(1) {
    this_thread::sleep_for(chrono::seconds(1));
    lock_guard<mutex> lg(log_mt);
    if (custmer.can_take()) {
      int temp = custmer.get().weight;
      cout << "THREAD " << this_thread::get_id() << " GET A STONE WEIGHT IS " << temp << "." << endl << endl;
    }
  }
}


int main() {
  // 缓冲区
  unique_ptr<Busket> pbusket(new Busket());

  // 生产者
  unique_ptr<Provider> pprovider(new Provider(200, *pbusket));

  // 消费者
  unique_ptr<Custmer> pcustmer(new Custmer(*pbusket));


  // boost线程池
  boost::thread_group threads;

  // 生产者
  threads.create_thread(boost::bind(func_provider, *pprovider));

  // 创建10个消费者
  for (int i = 0; i < 10; ++i) {
    threads.create_thread(boost::bind(func_custmer, *pcustmer));
  }

  // main函数阻塞
  threads.join_all();


  return 0;
}