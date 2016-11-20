#include "SaltyEngine/Scene.hpp"

namespace SaltyEngine
{

	Scene::Scene()
	{
	}


	Scene::~Scene()
	{
	}

	const std::string & Scene::GetName() const
	{
		return (m_name);
	}

	size_t Scene::GetSize() const
	{
		return (m_objects.size());
	}

	std::ostream &Scene::print(std::ostream &os) const
	{
		for (std::vector<std::unique_ptr<SaltyBehavior>>::const_iterator it = m_objects.begin(); it != m_objects.end(); it++)
		{
			os << "\t" << (**it) << std::endl;
		}
		return (os);
	}

	const std::unique_ptr<SaltyBehavior> &Scene::operator[](size_t index) const
	{
		return m_objects[index];
	}

	void Scene::OnStart()
	{
		while (!m_init.empty())
		{
			SaltyReflection<SaltyBehavior>::CallStart(GameObjects(), m_objects[m_init.front()].get());
			m_init.pop();
		}
	}

	void Scene::Update()
	{
		for (std::vector<std::unique_ptr<SaltyBehavior>>::const_iterator it = m_objects.begin(); it != m_objects.end(); it++)
			SaltyReflection<SaltyBehavior>::CallUpdate(GameObjects(), (*it).get());
	}

	void Scene::FixedUpdate()
	{
		for (std::vector<std::unique_ptr<SaltyBehavior>>::const_iterator it = m_objects.begin(); it != m_objects.end(); it++)
			SaltyReflection<SaltyBehavior>::CallFixedUpdate(GameObjects(), (*it).get());
	}

	void Scene::OnTriggerEnter()
	{
		for (std::vector<std::unique_ptr<SaltyBehavior>>::const_iterator it = m_objects.begin(); it != m_objects.end(); it++)
			SaltyReflection<SaltyBehavior>::CallOnTriggerEnter(GameObjects(), (*it).get());
	}

	void Scene::OnTriggerExit()
	{
		for (std::vector<std::unique_ptr<SaltyBehavior>>::const_iterator it = m_objects.begin(); it != m_objects.end(); it++)
			SaltyReflection<SaltyBehavior>::CallOnTriggerExit(GameObjects(), (*it).get());
	}

	void Scene::OnTriggerStay()
	{
		for (std::vector<std::unique_ptr<SaltyBehavior>>::const_iterator it = m_objects.begin(); it != m_objects.end(); it++)
			SaltyReflection<SaltyBehavior>::CallOnTriggerStay(GameObjects(), (*it).get());
	}

	void Scene::OnCollisionEnter()
	{
		for (std::vector<std::unique_ptr<SaltyBehavior>>::const_iterator it = m_objects.begin(); it != m_objects.end(); it++)
			SaltyReflection<SaltyBehavior>::CallOnCollisionEnter(GameObjects(), (*it).get());
	}

	void Scene::OnCollisionExit()
	{
		for (std::vector<std::unique_ptr<SaltyBehavior>>::const_iterator it = m_objects.begin(); it != m_objects.end(); it++)
			SaltyReflection<SaltyBehavior>::CallOnCollisionExit(GameObjects(), (*it).get());
	}

	void Scene::OnCollisionStay()
	{
		for (std::vector<std::unique_ptr<SaltyBehavior>>::const_iterator it = m_objects.begin(); it != m_objects.end(); it++)
			SaltyReflection<SaltyBehavior>::CallOnCollisionStay(GameObjects(), (*it).get());
	}

	void Scene::OnMouseEnter()
	{
		for (std::vector<std::unique_ptr<SaltyBehavior>>::const_iterator it = m_objects.begin(); it != m_objects.end(); it++)
			SaltyReflection<SaltyBehavior>::CallOnMouseEnter(GameObjects(), (*it).get());
	}

	void Scene::OnMouseExit()
	{
		for (std::vector<std::unique_ptr<SaltyBehavior>>::const_iterator it = m_objects.begin(); it != m_objects.end(); it++)
			SaltyReflection<SaltyBehavior>::CallOnMouseExit(GameObjects(), (*it).get());
	}

	void Scene::OnMouseOver()
	{
		for (std::vector<std::unique_ptr<SaltyBehavior>>::const_iterator it = m_objects.begin(); it != m_objects.end(); it++)
			SaltyReflection<SaltyBehavior>::CallOnMouseOver(GameObjects(), (*it).get());
	}

	void Scene::OnGui()
	{
		for (std::vector<std::unique_ptr<SaltyBehavior>>::const_iterator it = m_objects.begin(); it != m_objects.end(); it++)
			SaltyReflection<SaltyBehavior>::CallGui(GameObjects(), (*it).get());
	}

	void Scene::CallCoroutines()
	{
		for (std::vector<std::unique_ptr<SaltyBehavior>>::const_iterator it = m_objects.begin(); it != m_objects.end(); it++)
			(*it)->CallCoroutines();
	}

	void Scene::Clear()
	{
		m_objects.clear();
		while (!m_init.empty())
			m_init.pop();
	}
	void Scene::operator<<(SaltyBehavior *gameobj)
	{
		m_objects.push_back(std::unique_ptr<SaltyBehavior>(gameobj));
		m_init.emplace(m_objects.size() - 1);
	}
}

std::ostream & operator<<(std::ostream &os, SaltyEngine::Scene &scene)
{
	os << "Scene " << scene.GetName() << " :" << std::endl;
	return (os);
}

