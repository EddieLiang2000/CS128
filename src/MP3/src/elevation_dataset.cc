#include "elevation_dataset.hpp"

ElevationDataset::ElevationDataset(const std::string& filename, size_t width, size_t height): width_{width}, height_{height} {
    std::vector<int> temp = FileToVector(filename);
    max_ele_ = temp.at(0);
    min_ele_ = temp.at(0);
    if (temp.size() != width * height) {
        throw std::runtime_error("data size is incorrect");
    }  
    std::vector<int> row;
    for (unsigned int col = 0; col < temp.size(); col++) {
        row.push_back(temp.at(col));
        if (max_ele_ < temp.at(col)) {
            max_ele_ = temp.at(col);
        }
        if (min_ele_ > temp.at(col)) {
            min_ele_ = temp.at(col);
        }
        if (row.size() == width) {
            data_.push_back(row);
            row.clear();
        }
    }
}

std::vector<int> ElevationDataset::FileToVector(const std::string & filename) {
    std::ifstream ifs{filename};
    std::vector<int> output;
    int unit = 0;
    if (!ifs.is_open()) {
        throw std::runtime_error("file not open");
    }
    while (ifs.good()) {
        ifs >> unit;
        if (ifs.fail()) {
            ifs.clear();
            ifs.ignore(1, '\n');
        } else {
            output.push_back(unit);
        }
    }
    return output;
} 

size_t ElevationDataset::Height() const {
    return height_;
}

size_t ElevationDataset::Width() const {
    return width_;
}
  
int ElevationDataset::MaxEle() const {
    return max_ele_;
}

int ElevationDataset::MinEle() const {
    return min_ele_;
}
  
int ElevationDataset::DatumAt(size_t row, size_t col) const {
    if (row < 0 || row >= height_ || col < 0 || col >= width_) {
        throw std::runtime_error("invalid row or col");
    }
    return data_.at(row).at(col);
}

const std::vector<std::vector<int>> & ElevationDataset::GetData() const {
    return data_;
}

// for (std::string line; getline(ifs,line); line = "") {
    //     std::vector<int> row;
    //     std::string number = "";
    //     for (unsigned int i = 0; i <= line.length() + 1; i++) {
    //         if (line.at(i) == '-' || (line[i] >= '0' && line[i] <= '9')) {
    //             number += line[i];
    //         } else if ((line[i] == ' ' || i == line.length() + 1)){
    //             if (!number.empty()) {
    //                 row.push_back(std::stoi(number));
    //             }
    //             // std::cout << std::stoi(number) << std::endl;
    //             number = "";
    //         } else {
    //             throw std::runtime_error("invalid character or data");
    //         }
    //     }
    //     if (row.size() != width) {
    //         throw std::runtime_error("incorrect width");
    //     }
    //     data_.push_back(row);
    //     row.clear();
    // }
    // if (data_.size() != height) {
    //     throw std::runtime_error("incorrect height");
    // }
    // int unit;
    // while(ifs.good()) {
    //     ifs >> unit;
    //     // std::cout << unit << std::endl;
    //     if (ifs.fail()) {
    //         throw std::runtime_error("invalid data");
    //     } else if (row.size() < width) {
    //         row.push_back(unit);
    //         if (row.size() == width) {
    //             data_.push_back(row);
    //             row.clear();
    //         }
    //     }
    // }
    // if (row.size() > 0) {
    //     data_.push_back(row);
    // }