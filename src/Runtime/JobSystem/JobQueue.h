#pragma once
#include "Job.h"
#include <mutex> // For std::mutex
#include <queue>

class JobQueue {
public:
  void AddJob(const std::shared_ptr<Job>& job) {
    std::lock_guard<std::mutex> lock(QueueMutex);
    Jobs.push(job);
  }

  std::shared_ptr<Job> GetNextJob() {
    std::lock_guard<std::mutex> lock(QueueMutex);
    if (Jobs.empty())
      return nullptr;
    auto job = Jobs.front();
    Jobs.pop();
    return job;
  }

  bool IsEmpty() const {
    std::lock_guard<std::mutex> lock(QueueMutex);
    return Jobs.empty();
  }

private:
  std::queue<std::shared_ptr<Job>> Jobs;
  mutable std::mutex QueueMutex;
};
