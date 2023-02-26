#pragma once

#include <string>
#include <vector>
#include <ctime>

class Minesweeper {
public:
    struct Cell {
        size_t x = 0;
        size_t y = 0;

        bool operator<(const Cell& other) const;
    };

    enum class GameStatus {
        NOT_STARTED,
        IN_PROGRESS,
        VICTORY,
        DEFEAT,
    };

    struct CellStatus {
        int8_t number = 0;
        bool mine = false;
        bool marked = false;
        bool open = false;
    };

    using RenderedField = std::vector<std::string>;
    using GameField = std::vector<std::vector<CellStatus>>;

    Minesweeper(size_t width, size_t height, size_t mines_count);
    Minesweeper(size_t width, size_t height, const std::vector<Cell>& cells_with_mines);

    void NewGame(size_t width, size_t height, size_t mines_count);
    void NewGame(size_t width, size_t height, const std::vector<Cell>& cells_with_mines);

    void OpenCell(const Cell& cell);
    void MarkCell(const Cell& cell);

    void ShowInConsole() const;

    GameStatus GetGameStatus() const;
    time_t GetGameTime() const;

    RenderedField RenderField() const;

private:
    GameField field_;
    GameStatus status_;
    time_t game_start_ = 0;
    time_t game_end_ = 0;
    size_t cells_left_ = 0;

    void GameStart();
    void GameEnd();

    void AroundMine(std::size_t y, std::size_t x);

    bool IsCorrectCell(const Cell& cell);
};
