#include "path_image.hpp"
PathImage::PathImage(const GrayscaleImage & image, const ElevationDataset & dataset) {
    ConstructPaths(image, dataset);
    const Color kMarkred(252,25,63);
    const Color kMarkgreen(31,253,13);
    unsigned int least_ele_change = paths_.at(0).EleChange();
    size_t least_starting_row = paths_.at(0).StartingRow();
    unsigned int least_index = 0;
    for (unsigned int pathindex = 0; pathindex < paths_.size(); pathindex++) {
        Path path_object = paths_.at(pathindex);
        if ((path_object.EleChange() < least_ele_change) || 
            (path_object.EleChange() == least_ele_change && path_object.StartingRow() < least_starting_row)) {
            least_ele_change = path_object.EleChange();
            least_starting_row = path_object.StartingRow();
            least_index = pathindex;
            }
            const std::vector<size_t> & path = path_object.GetPath();
            for (unsigned int stepindex = 0; stepindex < path.size(); stepindex++) {
                path_image_.at(path.at(stepindex)).at(stepindex) = kMarkred;
        }
    }
    Path best_path_object = paths_.at(least_index);
    const std::vector<size_t> & best_path = best_path_object.GetPath();
    for (unsigned int stepindex = 0; stepindex < best_path.size(); stepindex++) {
        path_image_.at(best_path.at(stepindex)).at(stepindex) = kMarkgreen;
    }
}

void PathImage::ConstructPaths(const GrayscaleImage & image, const ElevationDataset & dataset) {
    size_t col = 0;
    path_image_ = image.GetImage();
    
    for (size_t row = 0; row < dataset.Height(); row++) {
        Path path(dataset.Width(), row);
        path.SetLoc(col, row);
        CalculatePath(path, dataset, row, col);
        paths_.push_back(path);
    }
    width_ = image.Width();
    height_ = image.Height();
}
  
size_t PathImage::Width() const {
    return width_;
}

size_t PathImage::Height() const {
    return height_;
}

unsigned int PathImage::MaxColorValue() const {
    return kMaxColorValue;
}

const std::vector<Path>& PathImage::Paths() const {
    return paths_;
}

const std::vector<std::vector<Color>> & PathImage::GetPathImage() const {
    return path_image_;
}

void PathImage::ToPpm(const std::string& name) const {
    std::ofstream ofs{name};
    ofs << "P3" << '\n' << width_ << " " << height_ << '\n' << kMaxColorValue << '\n';
    for (size_t row = 0; row < height_; row++) {
        for (size_t col = 0; col < width_; col++) {
            // std::cout << path_image_.at(row).at(col).Red() << std::endl;
            ofs << path_image_.at(row).at(col).Red() << ' ' << path_image_.at(row).at(col).Green() << ' ' << path_image_.at(row).at(col).Blue() << ' ';
        }
        ofs << '\n';
    }
}

void PathImage::CalculatePath(Path & path, const ElevationDataset & dataset, size_t row, size_t col) {
    if (static_cast<int>(row) - 1 >= 0 && (row + 1) <= (dataset.Height() - 1) && (col + 1) <= (dataset.Width() - 1)) {
        CalculatePathAll(path, dataset, row, col);
    } else if (static_cast<int>(row) - 1 >= 0 && col + 1 <= dataset.Width() - 1) {
        CalculatePathNorthEastAndEast(path, dataset, row, col);
    } else if (row + 1 <= dataset.Height() - 1 && col + 1 <= dataset.Width() - 1) {
        CalculatePathSouthEastAndEast(path, dataset, row, col);
    }
}

void PathImage::CalculatePathAll(Path & path, const ElevationDataset & dataset, size_t row, size_t col) {
    int current = dataset.DatumAt(row, col);

    unsigned int ne_dist = std::abs(dataset.DatumAt(row-1, col+1) - current);
    unsigned int e_dist = std::abs(dataset.DatumAt(row, col+1) - current);
    unsigned int se_dist = std::abs(dataset.DatumAt(row+1, col+1) - current);
    if (ne_dist < e_dist && ne_dist < se_dist) {
        path.IncEleChange(ne_dist);
        path.SetLoc(col+1, row-1);
        CalculatePath(path, dataset, row-1,col+1);
        
    } else if ((e_dist < ne_dist && e_dist < se_dist) || (e_dist == ne_dist && e_dist <= se_dist) || (e_dist == se_dist && e_dist <= ne_dist)) {
        path.IncEleChange(e_dist);
        path.SetLoc(col+1, row);
        
        CalculatePath(path, dataset, row,col+1);
        
    } else if ((se_dist < e_dist && se_dist < ne_dist) || (se_dist == ne_dist && se_dist < e_dist)) {
        path.IncEleChange(se_dist);
        path.SetLoc(col+1, row+1);
        
        CalculatePath(path, dataset, row+1,col+1);
        
    }
}

void PathImage::CalculatePathNorthEastAndEast(Path & path, const ElevationDataset & dataset, size_t row, size_t col) {
    int current = dataset.DatumAt(row, col);
    unsigned int ne_dist = std::abs(dataset.DatumAt(row-1, col+1) - current);
    unsigned int e_dist = std::abs(dataset.DatumAt(row, col+1) - current);
    if (ne_dist < e_dist) {
        path.IncEleChange(ne_dist);
        path.SetLoc(col+1, row-1);
        CalculatePath(path, dataset, row-1,col+1);
    } else {
        path.IncEleChange(e_dist);
        path.SetLoc(col+1, row);
        CalculatePath(path, dataset, row,col+1);
    }
}

void PathImage::CalculatePathSouthEastAndEast(Path & path, const ElevationDataset & dataset, size_t row, size_t col) {
    int current = dataset.DatumAt(row, col);
    unsigned int e_dist = std::abs(dataset.DatumAt(row, col+1) - current);
    unsigned int se_dist = std::abs(dataset.DatumAt(row+1, col+1) - current);
    if (se_dist < e_dist) {
        path.IncEleChange(se_dist);
        path.SetLoc(col+1, row+1);
        CalculatePath(path, dataset, row+1,col+1);
    } else {
        path.IncEleChange(e_dist);
        path.SetLoc(col+1, row);
        CalculatePath(path, dataset, row,col+1);
    }
}