# Rasterizer-and-Camera
Rasterizer for drawing scenes composed of 2D and 3D polygons

2D TRIANGLE RASTERIZATION:
  Classes edited:
    Rasterizer
    Polygon
  Rasterizer class contains a function named RenderScene() that returns a 512x512 QImage to be displayed in the GUI.

CONVEX POLYGON TRIANGULATION:
  Triangulate() function in Polygon class populates the Polygon's list of Triangles.

LINE SEGMENTS AND TRIANGLE RENDERING:
  Line Segment class contains:
    A constructor that takes in both endpoints of the line segment. The constructor makes use of an initialization list to assign values to all member variables.
    A function that computes the x-intersection of the line segment with a horizontal line based on the horizontal line's y-coordinate.
  Rasterizer class contains a function called RenderScene(), which now draws triangles on the QImage using Barycentric Interpolation

Implementation:
  
![image](https://github.com/JillRay973/Rasterizer-and-Camera/assets/143532365/738c38ad-a019-41ec-9d8b-b24fb5b658e8)
equilateral_triangle.json

![image](https://github.com/JillRay973/Rasterizer-and-Camera/assets/143532365/60cbac4e-63c9-439d-b38b-287c1c53fb6c)
polygons.json


3D TRIANGLE RASTERIZATION:
  PERSPECTIVE CAMERA:
    Camera class generates view matrices and perspective projection matrices. 
    Member Variables in class:
      A vector that represents the camera's "forward" direction, i.e. its Z axis. Default value of <0, 0, -1, 0>.
      A vector that represents the camera's "right" direction, i.e. its X axis. Default value of <1, 0, 0, 0>.
      A vector that represents the camera's "up" direction, i.e. its Y axis. Default value of <0, 1, 0, 0>.
      A value for the camera's vertical field of view. Default value of 45 degrees.
      A vector that represents the camera's position in world space. Default value of <0, 0, 10, 1>.
      A floating point number representing the camera's near clip plane. Default value of 0.01.
      A floating point number representing the camera's far clip plane. Default value of 100.0.
      A floating point number representing the camera's aspect ratio. Default value of 1.0.

  In the mainwindow file, there are also switch cases that call movement functions and toggle based on keypresses:
    A vector that represents the camera's "forward" direction, i.e. its Z axis. Default value of <0, 0, -1, 0>.
    A vector that represents the camera's "right" direction, i.e. its X axis. Default value of <1, 0, 0, 0>.
    A vector that represents the camera's "up" direction, i.e. its Y axis. Default value of <0, 1, 0, 0>.
    A value for the camera's vertical field of view. Default value of 45 degrees.
    A vector that represents the camera's position in world space. Default value of <0, 0, 10, 1>.
    A floating point number representing the camera's near clip plane. Default value of 0.01.
    A floating point number representing the camera's far clip plane. Default value of 100.0.
    A floating point number representing the camera's aspect ratio. Default value of 1.0.

PERSPECTIVE-CORRECT INTERPOLATION:
  Two methods of Barycentric interpolation have been implemented. First, interpolated each fragment's Z with correct perspective distortion, then interpolated each fragment's UVs with     correct perspective distortion.

TEXTURE MAPPING:
  Used the UV coordinates stored in each Vertex of the polygon mesh loaded from the OBJ file to map the texture colors to the surface of the polygon mesh using barycentric interpolation.

LAMBERTIAN REFLECTION:
  Used the UV coordinates stored in each Vertex of the polygon mesh loaded from the OBJ file to map the texture colors to the surface of the polygon mesh using barycentric interpolation.

RASTERIZED 3D RESULTS (with Lambertian Shading):

![image](https://github.com/JillRay973/Rasterizer-and-Camera/assets/143532365/d5aeaee7-2b83-4c97-a5a8-5170be11584e)
3D_wahoo.json

![image](https://github.com/JillRay973/Rasterizer-and-Camera/assets/143532365/7f00dd36-8a74-4a37-9cf2-138a5997c6dd)
3D_square.json

