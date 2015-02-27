#include <glm/glm.hpp>

class BoundingBox{

    std::vector<glm::vec3> vertices;
    glm::vec3 minVertex;
    glm::vec3 maxVertex;

public:
    BoundingBox(std::vector<glm::vec3> v);
    ~BoundingBox();

private:
    void createFromVertices();

};