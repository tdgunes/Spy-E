#include "BoundingBox.h"

void BoundingBox::createFromVertices(){

    float xmax = -100.0;
    float xmin = 100.0;
    float ymax = -100.0;
    float ymin = 100.0;
    float zmax = -100.0;
    float zmin = 100.0;

    for(int i = 0; i < vertices.size(); i++){

        glm::vec3 vertex = vertices[i];

        if(vertex.x > xmax) xmax = vertex.x;
        if(vertex.x < xmax) xmin = vertex.x;

        if(vertex.y > ymax) ymax = vertex.y;
        if(vertex.y < ymin) ymin = vertex.y;

        if(vertex.z > zmax) zmax = vertex.z;
        if(vertex.z < zmin) zmin = vertex.z;
    }

    minVertex = glm::vec3(xmin, ymin, zmin);
    maxVertex = glm::vec3(xmax, ymax, zmax);
}

BoundingBox::BoundingBox(std::vector<glm::vec3> v){

    vertices = v;
    createFromVertices();
}

BoundingBox::~BoundingBox(){

}

