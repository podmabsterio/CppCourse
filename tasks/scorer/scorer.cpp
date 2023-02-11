#include "scorer.h"
#include <unordered_map>

struct TaskStatus {
    bool cl_success = false;
    time_t cl_last_try = 0;
    bool merge_closed = true;
    time_t merge_last_try = 0;
};

ScoreTable GetScoredStudents(const Events& events, time_t score_time) {
    std::unordered_map<std::string, std::unordered_map<std::string, TaskStatus> > table;
    for (auto& event : events) {
        switch (event.event_type) {
            case EventType::CheckFailed:
                if (event.time > table[event.student_name][event.task_name].cl_last_try && event.time <= score_time) {
                    table[event.student_name][event.task_name].cl_last_try = event.time;
                    table[event.student_name][event.task_name].cl_success = false;
                }
                break;
            case EventType::CheckSuccess:
                if (event.time > table[event.student_name][event.task_name].cl_last_try && event.time <= score_time) {
                    table[event.student_name][event.task_name].cl_last_try = event.time;
                    table[event.student_name][event.task_name].cl_success = true;
                }
                break;
            case EventType::MergeRequestOpen:
                if (event.time > table[event.student_name][event.task_name].merge_last_try &&
                    event.time <= score_time) {
                    table[event.student_name][event.task_name].merge_last_try = event.time;
                    table[event.student_name][event.task_name].merge_closed = false;
                }
                break;
            case EventType::MergeRequestClosed:
                if (event.time > table[event.student_name][event.task_name].merge_last_try &&
                    event.time <= score_time) {
                    table[event.student_name][event.task_name].merge_last_try = event.time;
                    table[event.student_name][event.task_name].merge_closed = true;
                }
                break;
        }
    }
    ScoreTable complete_table;
    for (auto& [name, tasks] : table) {
        for (auto& [task_name, status] : tasks) {
            if (status.merge_closed && status.cl_success) {
                complete_table[name].insert(task_name);
            }
        }
    }
    return complete_table;
}
