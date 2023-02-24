#pragma once

#include <map>
#include <set>
#include <string>
#include <vector>
#include <unordered_map>

using StudentName = std::string;
using TaskName = std::string;

using ScoreTable = std::map<StudentName, std::set<TaskName>>;

struct TaskStatus {
    bool cl_success = false;
    bool merge_closed = true;
};

using InfoTable = std::unordered_map<std::string, std::unordered_map<std::string, TaskStatus> >;

class Scorer {
public:
    void OnCheckFailed(const StudentName& student_name, const TaskName& task_name);
    void OnCheckSuccess(const StudentName& student_name, const TaskName& task_name);
    void OnMergeRequestOpen(const StudentName& student_name, const TaskName& task_name);
    void OnMergeRequestClosed(const StudentName& student_name, const TaskName& task_name);
    void Reset();

    ScoreTable GetScoreTable() const;
private:
    InfoTable table_;

    void Cleaner(const StudentName& student_name, const TaskName& task_name);
};