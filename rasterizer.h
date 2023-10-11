#pragma once
#include <polygon.h>
#include <QImage>
#include <lineSegment.h>
#include <camera.h>

class Rasterizer
{
private:
    //This is the set of Polygons loaded from a JSON scene file
    std::vector<Polygon> m_polygons;
public:
    Rasterizer(const std::vector<Polygon>& polygons);

    QImage RenderScene();
    void ClearScene();
    Camera camera;
};
