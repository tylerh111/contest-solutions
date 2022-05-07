
#include <string>
#include <array>
#include <iostream>
#include <utility>


template <typename T, int mat_size>
struct Matrix {
    const int grid_size{mat_size};
    std::array<T, mat_size*mat_size> grid{};

    constexpr friend int get_index(const Matrix& mat, const int x, const int y) {
        return y*mat.grid_size + x;
    }

    constexpr friend std::pair<int, int> get_coord(const Matrix& mat, const int i) {
        return std::make_pair(i % mat.grid_size, i / mat.grid_size);
    }

    constexpr T& get_cell(const int i) { return grid.at(i); }
    constexpr const T& get_cell(const int i) const { return grid.at(i); }
    
    constexpr T& get_cell(const int x, const int y) { return grid.at(get_index(*this, x, y)); }
    constexpr const T& get_cell(const int x, const int y) const { return grid.at(get_index(*this, x, y)); }


};

template <int mat_size>
constexpr bool check_directions(const Matrix<bool, mat_size>& mat, int index) {
    auto coords = get_coord(mat, index);
    auto x = coords.first;
    auto y = coords.second;
    std::clog << x << ' ' << y << '\n';
    
    // right
    for (int i = x + 1; i < mat.grid_size; ++i) {
        std::clog << "( r): " << i << ' ' << y << '\n';
        if (mat.get_cell(i, y)) return false;
    }

    // left
    for (int i = x - 1; i >= 0; --i) {
        std::clog << "( l): " << i << ' ' << y << '\n';
        if (mat.get_cell(i, y)) return false;
    }

    // down
    for (int j = y + 1; j < mat.grid_size; ++j) {
        std::clog << "(d ): " << x << ' ' << j << '\n';
        if (mat.get_cell(x, j)) return false;
    }

    // up
    for (int j = y - 1; j >= 0; --j) {
        std::clog << "(u ): " << x << ' ' << j << '\n';
        if (mat.get_cell(x, j)) return false;
    }
        
    // down right
    for (int i = x + 1, j = y + 1; i < mat.grid_size && j < mat.grid_size; ++i, ++j) {
        std::clog << "(dr): " << i << ' ' << j << '\n';
        if (mat.get_cell(i, j)) return false;
    }
        
    // up left
    for (int i = x - 1, j = y - 1; i >= 0 && j >= 0; --i, --j) {
        std::clog << "(ul): " << i << ' ' << j << '\n';
        if (mat.get_cell(i, j)) return false;
    }

    // up right
    for (int i = x + 1, j = y - 1; i < mat.grid_size && j >= 0; ++i, --j) {
        std::clog << "(ur): " << i << ' ' << j << '\n';
        if (mat.get_cell(i, j)) return false;
    }

    // down left
    for (int i = x - 1, j = y + 1; i >= 0 && j < mat.grid_size; --i, ++j) {
        std::clog << "(dl): " << i << ' ' << j << '\n';
        if (mat.get_cell(i, j)) return false;
    }

    return true;
}


template <int mat_size>
constexpr bool solve(const Matrix<bool, mat_size>& mat) {

    for (int i = 0; i < static_cast<int>(mat.grid.size()); ++i) {
        auto& queen = mat.get_cell(i);
        if (!queen) continue;
        std::clog << i << "\n";
        if (!check_directions(mat, i)) return false;
    }

    return true;
}


int main() {
    
    constexpr int mat_size = 8;
    Matrix<bool, mat_size> mat;
    
    int queen_count = 0;
    for (auto& cell : mat.grid) {
        char cell_content;
        std::cin >> cell_content;
        if (cell_content == '*') {
            cell = true;
            ++queen_count;
        }
    }

    for (int y = 0; y < 8; y++) {
        for (int x = 0; x < 8; x++) {
            std::clog << mat.get_cell(x, y) << ' ';
        }
        std::clog << '\n';
    }

    if (queen_count == 8 && solve(mat)) {
        std::cout << "valid\n";
    }
    else {
        std::cout << "invalid\n";
    }

}


