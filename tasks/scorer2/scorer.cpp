#include "scorer.h"

ScoreTable Scorer::GetScoreTable() const {
    return complete_table_;
}

void Scorer::AddAndClean(const StudentName& student_name, const TaskName& task_name) {
    if (table_[student_name][task_name].cl_success && table_[student_name][task_name].merge_closed) {
        complete_table_[student_name].insert(task_name);
    } else {
        complete_table_[student_name].erase(task_name);
        if (complete_table_[student_name].empty()) {
            complete_table_.erase(student_name);
        }
    }
    if (!table_[student_name][task_name].cl_success && table_[student_name][task_name].merge_closed) {
        table_[student_name].erase(task_name);
    }
    if (table_[student_name].empty()) {
        table_.erase(student_name);
    }
}

void Scorer::OnCheckFailed(const StudentName& student_name, const TaskName& task_name) {
    table_[student_name][task_name].cl_success = false;
    this->AddAndClean(student_name, task_name);
}

void Scorer::OnCheckSuccess(const StudentName& student_name, const TaskName& task_name) {
    table_[student_name][task_name].cl_success = true;
    this->AddAndClean(student_name, task_name);
}

void Scorer::OnMergeRequestClosed(const StudentName& student_name, const TaskName& task_name) {
    table_[student_name][task_name].merge_closed = true;
    this->AddAndClean(student_name, task_name);
}

void Scorer::OnMergeRequestOpen(const StudentName& student_name, const TaskName& task_name) {
    table_[student_name][task_name].merge_closed = false;
    this->AddAndClean(student_name, task_name);
}

void Scorer::Reset() {
    table_.clear();
    complete_table_.clear();
}
