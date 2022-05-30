#include "Transform.h"

#include <iostream>

Transform::Transform()
{
}

Transform::~Transform()
{
}

glm::mat4 Transform::GetModelMatrix()
{
    // parent의 transfrom 불러오기
    glm::vec3 worldPosition{};
    glm::vec3 worldRotation{};
    glm::vec3 worldScale{};
    GetWorldPosition(worldPosition);
    GetWorldRotation(worldRotation);
    GetWorldScale(worldScale);

    glm::mat4 model = glm::mat4(1.0f);

    // scene 에서의 위치 변환
    model = glm::translate(model, worldPosition);

    // rotation 변환
    model = glm::rotate(model, glm::radians(worldRotation).z, glm::vec3(0.0f, 0.0f, 1.0f));
    model = glm::rotate(model, glm::radians(worldRotation).y, glm::vec3(0.0f, 1.0f, 0.0f));
    model = glm::rotate(model, glm::radians(worldRotation).x, glm::vec3(1.0f, 0.0f, 0.0f));

    // scale 변환
    model = glm::scale(model, worldScale);

    return model;
}

void Transform::ComputeWorldPosition(Transform* next, glm::vec3& outWorldPosition)
{
    if (next->m_parent != nullptr)
    {
        ComputeWorldPosition(next->m_parent, outWorldPosition);
        outWorldPosition += next->GetPosition();
    }
    else
    {
        outWorldPosition = next->GetPosition();
    }
}

void Transform::ComputeWorldRotation(Transform* next, glm::vec3& outWorldRotation)
{
    if (next->m_parent != nullptr)
    {
        ComputeWorldRotation(next->m_parent, outWorldRotation);
        outWorldRotation += next->GetRotation();
    }
    else
    {
        outWorldRotation = next->GetRotation();
    }
}

void Transform::ComputeWorldScale(Transform* next, glm::vec3& outWorldScale)
{
    if (next->m_parent != nullptr)
    {
        ComputeWorldScale(next->m_parent, outWorldScale);
        outWorldScale *= next->GetScale();
    }
    else
    {
        outWorldScale = next->GetScale();
    }
}

void Transform::GetWorldPosition(glm::vec3& outWorldPosition)
{
    ComputeWorldPosition(this, outWorldPosition);
}

void Transform::GetWorldRotation(glm::vec3& outWorldRotation)
{
    ComputeWorldRotation(this, outWorldRotation);
}

void Transform::GetWorldScale(glm::vec3& outWorldScale)
{
    ComputeWorldScale(this, outWorldScale);
}

void Transform::ComputeFront()
{
    glm::vec3 worldRotation{};
    GetWorldRotation(worldRotation);
    float pitch = worldRotation.x;
    float yaw = worldRotation.y;

    m_front.x = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    m_front.y = sin(glm::radians(pitch));
    m_front.z = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
}

void Transform::ComputeRight()
{
    ComputeFront();
    m_right = glm::normalize(glm::cross(GetFront(), GetUp()));
}