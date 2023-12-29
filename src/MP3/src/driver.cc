#include "elevation_dataset.hpp"
#include "grayscale_image.hpp"
#include "path_image.hpp"
#include <iostream>
int main() {
    
    ElevationDataset dataset("./example-data/ex_input_data/51w55h.dat",51,55);
    GrayscaleImage grayimage(dataset);
    // const ElevationDataset & test1ref = test1;
    // const GrayscaleImage & test2ref = test2;
    PathImage pathimage(grayimage,dataset);
    pathimage.ToPpm("./example-data/ex_output_paths/51w55h.ppm");
    return 0;
}