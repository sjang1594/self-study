# Concurrent Programming 5


## Source Code
unique_lock_and_lazy_init.cpp

### Unique_lock and Lazy Initialization
Different lock kind like lock_guard, but the unique_lock gives a better flexability than the lock_guard.

```
    std::unique_lock<mutex> locker(_mu);
      _f << "From " << id << ": " << value << endl;
      locker.unlock();
```

You can also construct locker without constructing the locker by using `unique_lock`. In order to do that, you need to pass the parameter like below

```
  std::unique_lock<mutex> locker (_mu, std::defer_lock);
```
The mutex has not locked yet, so than later, you can lock the mutex as following.

```
  std::unique_lock<mutex> locker (_mu, std::defer_lock);
  locker.lock();
```

Also, you can lock the mutex in any time(arbitary number...), which you can not do with `lock_guard`. The wrapper class? `lock_guard` or `unique_lock` cannot be copied, but `unique_lock` can be moved, but `lock_guard` cannot. When you move `unique_lock`, you are transferring the ownership of a mutex from one `unique_lock` to another `unique_lock`.
