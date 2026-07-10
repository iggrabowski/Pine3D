#pragma once
#include "Job.h"
#include "WorkerThread.h"
#include <thread>
#include <vector>

class JobSystem {
public:
  JobSystem(size_t numThreads) {
    for (size_t i = 0; i < numThreads; ++i) {
      Workers.emplace_back(std::make_unique<WorkerThread>(Queue));
      Workers.back()->Start();
    }
  }

  ~JobSystem() {
    for (auto& worker : Workers) {
      worker->Stop();
    }
  }

  void AddJob(const std::string& name, Job::JobFunction func) {
    auto job = std::make_shared<Job>(name, func);
    Queue.AddJob(job);
    ActiveJobs.push_back(job);
  }

  void WaitForAll() {
    for (auto& job : ActiveJobs) {
      while (!job->Completed()) {
        std::this_thread::yield();
      }
    }
    ActiveJobs.clear();
  }

  void ShowProgress() {
    for (const auto& job : ActiveJobs) {
      // ImGui::Text("%s: %.2f%%", job->GetName().c_str(), job->GetProgress() * 100.0f);
    }
  }

private:
  JobQueue Queue;
  std::vector<std::unique_ptr<WorkerThread>> Workers;
  std::vector<std::shared_ptr<Job>> ActiveJobs;
};
