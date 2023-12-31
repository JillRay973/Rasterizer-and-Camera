#include "polygon.h"
#include <glm/gtx/transform.hpp>
#include "lineSegment.h"

void Polygon::Triangulate()
{
    //TODO: Populate list of triangles

    m_tris.push_back(Triangle({0,1,2}));
   //was given the advice in class to use for loops, so i'm gonna use for loops lol

        for (unsigned int i = 3; i < m_verts.size(); i++){
        m_tris.push_back(Triangle({0, (i-1) , i}));
    }
}

glm::vec3 GetImageColor(const glm::vec2 &uv_coord, const QImage* const image)
{
    if(image)
    {
        int X = glm::min(image->width() * uv_coord.x, image->width() - 1.0f);
        int Y = glm::min(image->height() * (1.0f - uv_coord.y), image->height() - 1.0f);
        QColor color = image->pixel(X, Y);
        return glm::vec3(color.red(), color.green(), color.blue());
    }
    return glm::vec3(255.f, 255.f, 255.f);
}


// Creates a polygon from the input list of vertex positions and colors
Polygon::Polygon(const QString& name, const std::vector<glm::vec4>& pos, const std::vector<glm::vec3>& col)
    : m_tris(), m_verts(), m_name(name), mp_texture(nullptr), mp_normalMap(nullptr)
{
    for(unsigned int i = 0; i < pos.size(); i++)
    {
        m_verts.push_back(Vertex(pos[i], col[i], glm::vec4(), glm::vec2()));
    }
    Triangulate();
}

// Creates a regular polygon with a number of sides indicated by the "sides" input integer.
// All of its vertices are of color "color", and the polygon is centered at "pos".
// It is rotated about its center by "rot" degrees, and is scaled from its center by "scale" units
Polygon::Polygon(const QString& name, int sides, glm::vec3 color, glm::vec4 pos, float rot, glm::vec4 scale)
    : m_tris(), m_verts(), m_name(name), mp_texture(nullptr), mp_normalMap(nullptr)
{
    glm::vec4 v(0.f, 1.f, 0.f, 1.f);
    float angle = 360.f / sides;
    for(int i = 0; i < sides; i++)
    {
        glm::vec4 vert_pos = glm::translate(glm::vec3(pos.x, pos.y, pos.z))
                           * glm::rotate(rot, glm::vec3(0.f, 0.f, 1.f))
                           * glm::scale(glm::vec3(scale.x, scale.y, scale.z))
                           * glm::rotate(i * angle, glm::vec3(0.f, 0.f, 1.f))
                           * v;
        m_verts.push_back(Vertex(vert_pos, color, glm::vec4(), glm::vec2()));
    }

    Triangulate();
}

Polygon::Polygon(const QString &name)
    : m_tris(), m_verts(), m_name(name), mp_texture(nullptr), mp_normalMap(nullptr)
{}

Polygon::Polygon()
    : m_tris(), m_verts(), m_name("Polygon"), mp_texture(nullptr), mp_normalMap(nullptr)
{}

Polygon::Polygon(const Polygon& p)
    : m_tris(p.m_tris), m_verts(p.m_verts), m_name(p.m_name), mp_texture(nullptr), mp_normalMap(nullptr)
{
    if(p.mp_texture != nullptr)
    {
        mp_texture = new QImage(*p.mp_texture);
    }
    if(p.mp_normalMap != nullptr)
    {
        mp_normalMap = new QImage(*p.mp_normalMap);
    }
}

Polygon::~Polygon()
{
    delete mp_texture;
}

void Polygon::SetTexture(QImage* i)
{
    mp_texture = i;
}

void Polygon::SetNormalMap(QImage* i)
{
    mp_normalMap = i;
}

void Polygon::AddTriangle(const Triangle& t)
{
    m_tris.push_back(t);
}

void Polygon::AddVertex(const Vertex& v)
{
    m_verts.push_back(v);
}

void Polygon::ClearTriangles()
{
    m_tris.clear();
}

Triangle& Polygon::TriAt(unsigned int i)
{
    return m_tris[i];
}

Triangle Polygon::TriAt(unsigned int i) const
{
    return m_tris[i];
}

Vertex &Polygon::VertAt(unsigned int i)
{
    return m_verts[i];
}

Vertex Polygon::VertAt(unsigned int i) const
{
    return m_verts[i];
}

glm::vec4 Polygon::bounding_box(Triangle t) {
    float left = 1000, right = -1000, top = -1000, bottom = 1000;
    glm::vec4 v;
    for(int i = 0; i < 3; i++) {
        v = m_verts[t.m_indices[i]].m_pos;
        if(v[0] < left) {
            left = v[0];
        }
        if(v[0] > right) {
            right = v[0];
        }
        if(v[1] < bottom) {
            bottom = v[1];
        }
        if(v[1] > top) {
            top = v[1];
        }
    }
    return glm::vec4(left, right, top, bottom);
}

glm::vec3 Polygon::barycentric(Triangle t, float x, float y) {
    glm::vec4 a = m_verts[t.m_indices[0]].m_pos, b = m_verts[t.m_indices[1]].m_pos,
        c = m_verts[t.m_indices[2]].m_pos, p = glm::vec4(x, y, 0, 1);
    glm::vec3 l1 = glm::vec3(b[0] - a[0], b[1] - a[1], 0);
    glm::vec3 l2 = glm::vec3(c[0] - a[0], c[1] - a[1], 0);
    float Area = glm::length(glm::cross(l1, l2));
    l1 = glm::vec3(b[0] - p[0], b[1] - p[1], 0);
    l2 = glm::vec3(c[0] - p[0], c[1] - p[1], 0);
    float A = glm::length(glm::cross(l1, l2));
    l1 = glm::vec3(a[0] - p[0], a[1] - p[1], 0);
    l2 = glm::vec3(c[0] - p[0], c[1] - p[1], 0);
    float B = glm::length(glm::cross(l1, l2));
    l1 = glm::vec3(a[0] - p[0], a[1] - p[1], 0);
    l2 = glm::vec3(b[0] - p[0], b[1] - p[1], 0);
    float C = glm::length(glm::cross(l1, l2));

    return glm::vec3(A / Area, B / Area, C / Area);
}

