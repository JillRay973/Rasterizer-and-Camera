#pragma once
#include <glm/glm.hpp>

class lineSegment
{
private:
    //vec4 so can easily use with Vertex class
    glm::vec4 a, b;
    bool vertical;
    float slope;
public:
   lineSegment();
   lineSegment(glm::vec4 a, glm::vec4 b);

    bool findIntersection(float y, float* x_intersect);
};

