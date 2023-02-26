#include <random>
#include <algorithm>
#include <iostream>
#include <queue>
#include <set>
#include <tuple>

#include "minesweeper.h"

size_t CorrectDecrement(size_t coordinate) {
    size_t correct = 0;
    if (coordinate > 0) {
        correct = coordinate - 1;
    }
    return correct;
}

void Minesweeper::AroundMine(std::size_t y, std::size_t  x) {
    for (auto i = CorrectDecrement(x); i <= x + 1; ++i) {
        for (auto j = CorrectDecrement(y); j <= y + 1; ++j) {
            if (IsCorrectCell(Cell{i, j})) {
                field_[j][i].number++;
            }
        }
    }
}

//void Minesweeper::MakeBorders() {
//    for (size_t i = 0; i < field_.size(); ++i) {
//        field_[i][0].number = 1;
//        field_[i].back().number = 1;
//    }
//    for (size_t i = 0; i < field_[0].size(); ++i) {
//        field_[0][i].number = 1;
//        field_.back()[i].number = 1;
//    }
//}

bool Minesweeper::IsCorrectCell(const Minesweeper::Cell& cell) {
    return cell.y < field_.size() and cell.x < field_[0].size();
}

Minesweeper::Minesweeper(size_t width, size_t height, size_t mines_count) :
      field_(GameField(height, std::vector<CellStatus>(width))) {

    status_ = GameStatus::NOT_STARTED;
    cells_left_ = width * height;

    std::vector<bool> generator(std::min(width * height, mines_count), true);
    generator.resize(width * height, false);

    auto seed = std::random_device {};
    auto random_engine = std::default_random_engine { seed() };
    std::shuffle(std::begin(generator), std::end(generator), random_engine);

    for (size_t i = 0; i < generator.size(); ++i) {
        if (generator[i]) {
            AroundMine(i / width, i % width);
            field_[i / width][i % width].mine = true;
            --cells_left_;
        }
    }
}

Minesweeper::Minesweeper(size_t width, size_t height, const std::vector<Cell> &cells_with_mines) :
      field_(GameField(height, std::vector<CellStatus>(width))) {

    status_ = GameStatus::NOT_STARTED;
    cells_left_ = width * height;

    for (auto& mine : cells_with_mines) {
        if (!field_[mine.y][mine.x].mine) {
            --cells_left_;
        }
        AroundMine(mine.y, mine.x);
        field_[mine.y][mine.x].mine = true;
    }
}

void Minesweeper::NewGame(size_t width, size_t height, size_t mines_count) {
    *this = Minesweeper(width, height, mines_count);
}

void Minesweeper::NewGame(size_t width, size_t height, const std::vector<Cell>& cells_with_mines) {
    *this = Minesweeper(width, height, cells_with_mines);
}

Minesweeper::GameStatus Minesweeper::GetGameStatus() const {
    return status_;
}

time_t Minesweeper::GetGameTime() const {
    return game_end_ - game_start_;
}

void Minesweeper::GameStart() {
    if (status_ == GameStatus::NOT_STARTED) {
        game_start_ = std::time(0);
        status_ = GameStatus::IN_PROGRESS;
    }
}

void Minesweeper::GameEnd() {
    if (status_ == GameStatus::DEFEAT) {
        game_end_ = std::time(0);
        return;
    }
    if (cells_left_ == 0) {
        status_ = GameStatus::VICTORY;
        game_end_ = std::time(0);
    }
}

void Minesweeper::MarkCell(const Cell& cell) {
    GameStart();
    if (status_ == GameStatus::IN_PROGRESS) {
        field_[cell.y][cell.x].marked ^= true;
    }
}

void Minesweeper::OpenCell(const Cell& cell) {
    GameStart();
    if (status_ != GameStatus::IN_PROGRESS or field_[cell.y][cell.x].marked or field_[cell.y][cell.x].open) {
        return;
    }
    if (field_[cell.y][cell.x].mine) {
        status_ = GameStatus::DEFEAT;
        GameEnd();
        return;
    }
    if (field_[cell.y][cell.x].number > 0) {
        field_[cell.y][cell.x].open = true;
        --cells_left_;
        GameEnd();
        return;
    }

    std::queue<Cell> not_processed;
    std::set<Cell> processed;
    not_processed.push(cell);
    while (!not_processed.empty()) {
        Cell next_cell = not_processed.front();
        not_processed.pop();
        if (processed.count(next_cell)) {
            continue;
        }
        processed.insert(next_cell);
        if (field_[next_cell.y][next_cell.x].marked) {
            continue;
        }
        --cells_left_;
        GameEnd();
        field_[next_cell.y][next_cell.x].open = true;
        if (field_[next_cell.y][next_cell.x].number > 0) {
            continue;
        }
        for (size_t i = CorrectDecrement(next_cell.y); i <= next_cell.y + 1; ++i) {
            for (size_t j = CorrectDecrement(next_cell.x); j <= next_cell.x + 1; ++j) {
                if (IsCorrectCell({j, i}) && (i != next_cell.y || j != next_cell.x)) {
                    not_processed.push({j, i});
                }
            }
        }
    }
}

char CellToChar(Minesweeper::CellStatus cell) {
    if (cell.mine) {
        return '*';
    }
    if (cell.number == 0) {
        return '.';
    }
    return static_cast<char>(cell.number + '0');
}

Minesweeper::RenderedField Minesweeper::RenderField() const {
    RenderedField representation;
    for (size_t i = 0; i < field_.size(); ++i) {
        representation.emplace_back("");
        for (size_t j = 0; j < field_[i].size(); ++j) {
            if (field_[i][j].open or status_ == GameStatus::DEFEAT) {
                representation.back() += CellToChar(field_[i][j]);
            } else if (field_[i][j].marked) {
                representation.back() += '?';
            } else {
                representation.back() += '-';
            }
        }
    }
    return representation;
}

void Minesweeper::ShowInConsole() const {
    for (auto& line : this->RenderField()) {
        std::cout << line << "\n";
    }
}

bool Minesweeper::Cell::operator<(const Minesweeper::Cell& other) const {
    return std::tie(this->x, this->y) < std::tie(other.x, other.y);
}
