#pragma once
#include <glad/glad.h> 
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Transform
{
protected:
	Transform* m_parent = nullptr;
	glm::vec3 m_position{ 0.0f, 0.0f, 0.0f };
	glm::vec3 m_rotation{ 0.0f, 0.0f, 0.0f };
	glm::vec3 m_scale{ 1.0f, 1.0f, 1.0f };
	glm::vec3 m_front{ 0.0f, 0.0f, 0.0f };
	glm::vec3 m_right{ 0.0f, 0.0f, 0.0f };
	const glm::vec3 m_up = { 0.0f, 1.0f, 0.0f };

public:
	// 부모 Transform을 가져옵니다.
	inline Transform* GetParent() { return m_parent; }
	// Transform을 부모 Transform에 붙입니다.
	inline void SetParent(Transform* parent) { m_parent = parent; }
	inline glm::vec3 GetPosition() const { return m_position; }
	inline void SetPosition(const glm::vec3& position) { m_position = position; }
	inline void AddPosition(const glm::vec3& position) { m_position += position; }
	inline glm::vec3 GetRotation() const { return m_rotation; }
	inline void SetRotation(const glm::vec3& rotation) { m_rotation = rotation; }
	inline void AddRotation(const glm::vec3& rotation) { m_rotation += rotation; }
	inline glm::vec3 GetScale() const { return m_scale; }
	inline void SetScale(const glm::vec3& scale) { m_scale = scale; }
	inline glm::vec3 GetFront() { ComputeFront(); return m_front; }
	inline glm::vec3 GetRight() { ComputeRight(); return m_right; }
	inline glm::vec3 GetUp() { return m_up; }
public:
	Transform();
	virtual ~Transform();
	// Transform으로 변환된 Mat4를 반환합니다.
	glm::mat4 GetModelMatrix();

	void GetWorldPosition(glm::vec3& outWorldPosition);
	void GetWorldRotation(glm::vec3& outWorldRotation);
	void GetWorldScale(glm::vec3& outWorldScale);
private:
	void ComputeFront();
	void ComputeRight();
	void ComputeWorldPosition(Transform* next, glm::vec3& outWorldPosition);
	void ComputeWorldRotation(Transform* next, glm::vec3& outWorldRotation);
	void ComputeWorldScale   (Transform* next, glm::vec3& outWorldScale);
};

