#include "scorer.h"

ScoreTable Scorer::GetScoreTable() const {
    ScoreTable complete_table;
    for (auto& [name, tasks] : table_) {
        for (auto& [task_name, status] : tasks) {
            if (status.merge_closed && status.cl_success) {
                complete_table[name].insert(task_name);
            }
        }
    }
    return complete_table;
}

void Scorer::Cleaner(const StudentName& student_name, const TaskName& task_name) {
    if (!table_[student_name][task_name].cl_success && table_[student_name][task_name].merge_closed) {
        table_[student_name].erase(task_name);
    }
    if (table_[student_name].empty()) {
        table_.erase(student_name);
    }
}

void Scorer::OnCheckFailed(const StudentName& student_name, const TaskName& task_name) {
    table_[student_name][task_name].cl_success = false;
    this->Cleaner(student_name, task_name);
}

void Scorer::OnCheckSuccess(const StudentName& student_name, const TaskName& task_name) {
    table_[student_name][task_name].cl_success = true;
}

void Scorer::OnMergeRequestClosed(const StudentName& student_name, const TaskName& task_name) {
    table_[student_name][task_name].merge_closed = false;
}

void Scorer::OnMergeRequestOpen(const StudentName& student_name, const TaskName& task_name) {
    table_[student_name][task_name].merge_closed = true;
    this->Cleaner(student_name, task_name);
}

void Scorer::Reset() {
    table_.clear();
}


