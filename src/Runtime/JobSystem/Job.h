#pragma once
#include <atomic>
#include <functional>
#include <string>

class Job {
public:
  using JobFunction = std::function<void(std::atomic<float>&)>;

  Job(const std::string& name, JobFunction func)
      : Name(name)
      , Task(func)
      , Progress(0.0f)
      , IsCompleted(false) {}

  void Execute() {
    Task(Progress);
    IsCompleted = true;
  }

  const std::string& GetName() const { return Name; }
  float GetProgress() const { return Progress.load(); }
  bool Completed() const { return IsCompleted; }

private:
  std::string Name;
  JobFunction Task;
  std::atomic<float> Progress;
  std::atomic<bool> IsCompleted;
};
