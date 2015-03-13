

#ifndef _SPYE_ENTITY_H_
#define _SPYE_ENTITY_H_

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>


class Entity {

protected:

public:
    glm::vec3 position;
    glm::quat orientation;
    glm::mat4 transformation;


    Entity();
    glm::mat4& getTransformation() {
        transformation = glm::toMat4(orientation);
        transformation[3][0] = position[0];
        transformation[3][1] = position[1];
        transformation[3][2] = position[2];
        return transformation;

    }
    void setTransformation(glm::mat4& trans) {
        orientation = glm::normalize(glm::toQuat(trans));
        position = glm::vec3(trans[3]);
    }

    glm::quat getOrientation() const;
    void setOrientation(glm::quat &orientation);
    glm::vec3 getPosition() const;
    void setPosition(glm::vec3 &position);
};

#endif