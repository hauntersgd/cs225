/**
 * @file maptiles.cpp
 * Code for the maptiles function.
 */

#include <iostream>
#include <map>

#include "maptiles.h"

using namespace std;


Point<3> convertToXYZ(LUVAPixel pixel) {
    return Point<3>( pixel.l, pixel.u, pixel.v );
}

MosaicCanvas* mapTiles(SourceImage const& theSource,
                       vector<TileImage>& theTiles)
{
    /**
     * @todo Implement this function!
     */

    std::map<Point<3>, TileImage> m;
    int rows = theSource.getRows();
    int columns = theSource.getColumns();
    MosaicCanvas* mosaic = new MosaicCanvas(rows, columns);
    vector<Point<3>> tileAverage;
    for(auto it = theTiles.begin(); it!= theTiles.end(); it++) {
        Point<3> tilePixel = convertToXYZ(it->getAverageColor());
        m[tilePixel] = *it;
        tileAverage.push_back(tilePixel);
    }
    KDTree<3> kd = KDTree<3>(tileAverage);

    for(int row = 0; row < rows; row++) {
        for(int column = 0; column < columns; column++) {
            LUVAPixel pixel = theSource.getRegionColor(row, column);
            Point<3> average = convertToXYZ(pixel);
            Point<3> closest = kd.findNearestNeighbor(average); // nearest neighbor doesnt exist
            TileImage* image = new TileImage(m[closest]);
            mosaic->setTile(row, column, image);
        }
    }


    return mosaic;
}

