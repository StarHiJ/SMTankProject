#include "AttackModel.h"

AttackModel::AttackModel(std::string const& path, bool gamma, Transform* parent)
	: Model(path, gamma , parent)
{
}

void AttackModel::Draw(class Shader& shader)
{
	if (!m_visible)
	{
		return;
	}
	if (m_range > m_maxRange)
	{
		m_gravityVelocity = 0.0f;
		m_range = 0.0f;
		m_visible = false;
		return;
	}
	if (m_bSiege)
	{
		m_gravityVelocity += m_gravity * m_deltaTime;
		AddPosition(glm::vec3(0.0f, -m_gravityVelocity, 0.0f));
	}

	glm::vec3 velocity = GetFront() * m_velocity * m_deltaTime;
	AddPosition(velocity);
	m_range += m_velocity * m_deltaTime;
	Model::Draw(shader);
}

void AttackModel::TankAttack()
{
	m_bSiege = false;
	m_velocity = 40.0f;
	m_maxRange = 40.0f;
	Run();
	SetScale(glm::vec3(0.1f, 0.1f, 0.1f));
	AddPosition(glm::vec3(0.0f, 0.17f, 0.0f));
}

void AttackModel::SiegeTankAttack()
{
	m_bSiege = true;
	m_gravityVelocity = -5.0f * m_deltaTime;
	m_velocity = 40.0f;
	m_maxRange = 80.0f;
	Run();
	SetScale(glm::vec3(0.25f, 0.25f, 0.25f));
	AddPosition(glm::vec3(0.0f, 0.2f, 0.0f));
}

void AttackModel::Run()
{
	m_visible = true;
	m_range = 0.0f;
	glm::vec3 velocity = GetFront() * m_deltaTime * 20.0f;
	AddPosition(velocity);
}
