#pragma once

#include <../lib/glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "glm/ext/matrix_transform.hpp"
#include "glm/ext/quaternion_geometric.hpp"
#include "glm/fwd.hpp"
#include "glm/gtc/quaternion.hpp"
#include "iostream"
#include "math.h"
#include "quat.hpp"
#include "vec3.hpp"

struct Mat4 {
    glm::mat4 matrix;
    float* data = glm::value_ptr(matrix);

    Mat4(float initializer = 0.0f) {
        matrix = glm::mat4(initializer);
        data   = glm::value_ptr(matrix);
    }

    Mat4(glm::mat4 mat) {
        matrix = mat;
        data   = glm::value_ptr(matrix);
    }

    float* Value() { return glm::value_ptr(matrix); }

    float& Set(unsigned int row, unsigned int col) { return data[row + (col * 4)]; }

    Vec3 Forward() const {
        const glm::mat4 inv     = glm::inverse(matrix);
        const glm::vec3 forward = glm::normalize(glm::vec3(inv[2]));
        return Vec3(forward.x, forward.y, -forward.z);
    }

    Vec3 Left() const {
        const glm::mat4 inv  = glm::inverse(matrix);
        const glm::vec3 left = glm::normalize(glm::vec3(inv[0]));
        return Vec3(left.x, left.y, left.z);
    }

    Vec3 Up() const {
        const glm::mat4 inv = glm::inverse(matrix);
        const glm::vec3 up  = glm::normalize(glm::vec3(inv[1]));
        return Vec3(up.x, up.y, up.z);
    }

    Vec3 Translate(Vec3 pos) {
        matrix           = glm::translate(matrix, glm::vec3(pos.x, pos.y, pos.z));
        glm::vec3 newPos = glm::vec3(matrix[3]);

        return Vec3(newPos.x, newPos.y, newPos.z);
    }

    Vec3 SetPosition(Vec3 pos) {
        Set(0, 3) = pos.x;
        Set(1, 3) = pos.y;
        Set(2, 3) = pos.z;

        glm::vec3 newPos = glm::vec3(matrix[3]);
        return Vec3(newPos.x, newPos.y, newPos.z);
    }

    void Scale(Vec3 scale) {
        Set(0, 0) *= scale.x;
        Set(1, 1) *= scale.y;
        Set(2, 2) *= scale.z;
    }

    Quat Rotate(Quat rot) {
        glm::vec3 axis = glm::normalize(glm::vec3(rot.x, rot.y, rot.z));
        matrix         = glm::rotate(matrix, rot.w, axis);

        glm::quat quatRot;
        float dataRot[16] = {
            matrix[0][0],
            matrix[0][1],
            matrix[0][2],
            0,
            matrix[1][0],
            matrix[1][1],
            matrix[1][2],
            0,
            matrix[2][0],
            matrix[2][1],
            matrix[2][2],
            0,
            0,
            0,
            0,
            1,
        };

        glm::mat4 matRot = glm::make_mat4(dataRot);
        quatRot          = glm::quat_cast(matRot);

        return Quat(quatRot.w, quatRot.x, quatRot.y, quatRot.z);
    }

    void Perspective(float fov, float aspect, float near, float far) {
        matrix = glm::perspective(fov, aspect, near, far);
    }
};
