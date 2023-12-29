#include "grayscale_image.hpp"
GrayscaleImage::GrayscaleImage(const ElevationDataset& dataset) {
    DatasetToGrayscale(dataset);
    width_ = dataset.Width();
    height_ = dataset.Height();
}

GrayscaleImage::GrayscaleImage(const std::string & filename, size_t width, size_t height) {
    ElevationDataset dataset(filename, width, height);
    const ElevationDataset & datasetref = dataset;
    DatasetToGrayscale(datasetref);
    width_ = dataset.Width();
    height_ = dataset.Height();
}

size_t GrayscaleImage::Width() const {
    return width_;
}
size_t GrayscaleImage::Height() const {
    return height_;
}
unsigned int GrayscaleImage::MaxColorValue() const {
    return kMaxColorValue;
}

const Color & GrayscaleImage::ColorAt(int row, int col) const {
    return image_.at(row).at(col);
}

const std::vector<std::vector<Color>> & GrayscaleImage::GetImage() const {
    return image_;
}

void GrayscaleImage::ToPpm( const std::string& name ) const {
    std::ofstream ofs{name};
    ofs << "P3" << '\n' << width_ << " " << height_ << '\n' << kMaxColorValue << '\n';
    for (size_t row = 0; row < height_; row++) {
        for (size_t col = 0; col < width_; col++) {
            ofs << image_.at(row).at(col).Red() << ' ' << image_.at(row).at(col).Green() << ' ' << image_.at(row).at(col).Blue() << ' ';
        }
        ofs << '\n';
    }
}

void GrayscaleImage::DatasetToGrayscale(const ElevationDataset& dataset) {
    for (size_t row = 0; row < dataset.Height(); row++) {
        std::vector<Color> rows;
        for (size_t col = 0; col < dataset.Width(); col++) {
            int shade_of_gray = 0;
            if (dataset.MaxEle() == dataset.MinEle()) {
                shade_of_gray = 0;
            } else {
                int elevationpoint = dataset.DatumAt(row, col);
                // std::cout << "elevation is: " << elevationpoint << std::endl;
                // std::cout << "Max is: " << dataset.MaxEle() << std::endl;
                // std::cout << "Min is: " << dataset.MinEle() << std::endl;
                // double shades = (double(elevationpoint - dataset.MinEle())) / (dataset.MaxEle() - dataset.MinEle()) * 255;
                // std::cout << "Shade is: " << shades << std::endl;
                shade_of_gray = std::round((double(elevationpoint - dataset.MinEle())) / (dataset.MaxEle() - dataset.MinEle()) * kMaxColorValue);
                // std::cout << "in scope" << shade_of_gray << std::endl;
            }
            // std::cout << "out of scope" << shade_of_gray << std::endl;
            Color shade_color(shade_of_gray, shade_of_gray, shade_of_gray);
            rows.push_back(shade_color);
        }
        image_.push_back(rows);
    }
}

