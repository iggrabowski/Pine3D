#pragma once
#include "JobQueue.h"
#include <atomic> // For std::atomic
#include <thread> // For std::thread

class WorkerThread {
public:
  WorkerThread(JobQueue& queue)
      : JobQueueRef(queue)
      , StopFlag(false) {}

  void Start() {
    Worker = std::thread([this]() {
      while (!StopFlag) {
        auto job = JobQueueRef.GetNextJob();
        if (job) {
          job->Execute();
        } else {
          std::this_thread::sleep_for(std::chrono::milliseconds(10));
        }
      }
    });
  }

  void Stop() {
    StopFlag = true;
    if (Worker.joinable())
      Worker.join();
  }

private:
  JobQueue& JobQueueRef;
  std::thread Worker;
  std::atomic<bool> StopFlag;
};
