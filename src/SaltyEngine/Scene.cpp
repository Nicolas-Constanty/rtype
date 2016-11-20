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
		for (std::vector<std::unique_ptr<SaltyBehaviour>>::const_iterator it = m_objects.begin(); it != m_objects.end(); it++)
		{
			os << "\t" << (**it) << std::endl;
		}
		return (os);
	}

	const std::unique_ptr<SaltyBehaviour> &Scene::operator[](size_t index) const
	{
		return m_objects[index];
	}

	void Scene::OnStart()
	{
		while (!m_init.empty())
		{
			SaltyReflection<SaltyBehaviour>::CallStart(GameObjects(), m_objects[m_init.front()].get());
			m_init.pop();
		}
	}

	void Scene::Update()
	{
		for (std::vector<std::unique_ptr<SaltyBehaviour>>::const_iterator it = m_objects.begin(); it != m_objects.end(); it++)
			SaltyReflection<SaltyBehaviour>::CallUpdate(GameObjects(), (*it).get());
	}

	void Scene::FixedUpdate()
	{
		for (std::vector<std::unique_ptr<SaltyBehaviour>>::const_iterator it = m_objects.begin(); it != m_objects.end(); it++)
			SaltyReflection<SaltyBehaviour>::CallFixedUpdate(GameObjects(), (*it).get());
	}

	void Scene::OnTriggerEnter()
	{
		for (std::vector<std::unique_ptr<SaltyBehaviour>>::const_iterator it = m_objects.begin(); it != m_objects.end(); it++)
			SaltyReflection<SaltyBehaviour>::CallOnTriggerEnter(GameObjects(), (*it).get());
	}

	void Scene::OnTriggerExit()
	{
		for (std::vector<std::unique_ptr<SaltyBehaviour>>::const_iterator it = m_objects.begin(); it != m_objects.end(); it++)
			SaltyReflection<SaltyBehaviour>::CallOnTriggerExit(GameObjects(), (*it).get());
	}

	void Scene::OnTriggerStay()
	{
		for (std::vector<std::unique_ptr<SaltyBehaviour>>::const_iterator it = m_objects.begin(); it != m_objects.end(); it++)
			SaltyReflection<SaltyBehaviour>::CallOnTriggerStay(GameObjects(), (*it).get());
	}

	void Scene::OnCollisionEnter()
	{
		for (std::vector<std::unique_ptr<SaltyBehaviour>>::const_iterator it = m_objects.begin(); it != m_objects.end(); it++)
			SaltyReflection<SaltyBehaviour>::CallOnCollisionEnter(GameObjects(), (*it).get());
	}

	void Scene::OnCollisionExit()
	{
		for (std::vector<std::unique_ptr<SaltyBehaviour>>::const_iterator it = m_objects.begin(); it != m_objects.end(); it++)
			SaltyReflection<SaltyBehaviour>::CallOnCollisionExit(GameObjects(), (*it).get());
	}

	void Scene::OnCollisionStay()
	{
		for (std::vector<std::unique_ptr<SaltyBehaviour>>::const_iterator it = m_objects.begin(); it != m_objects.end(); it++)
			SaltyReflection<SaltyBehaviour>::CallOnCollisionStay(GameObjects(), (*it).get());
	}

	void Scene::OnMouseEnter()
	{
		for (std::vector<std::unique_ptr<SaltyBehaviour>>::const_iterator it = m_objects.begin(); it != m_objects.end(); it++)
			SaltyReflection<SaltyBehaviour>::CallOnMouseEnter(GameObjects(), (*it).get());
	}

	void Scene::OnMouseExit()
	{
		for (std::vector<std::unique_ptr<SaltyBehaviour>>::const_iterator it = m_objects.begin(); it != m_objects.end(); it++)
			SaltyReflection<SaltyBehaviour>::CallOnMouseExit(GameObjects(), (*it).get());
	}

	void Scene::OnMouseOver()
	{
		for (std::vector<std::unique_ptr<SaltyBehaviour>>::const_iterator it = m_objects.begin(); it != m_objects.end(); it++)
			SaltyReflection<SaltyBehaviour>::CallOnMouseOver(GameObjects(), (*it).get());
	}

	void Scene::OnGui()
	{
		for (std::vector<std::unique_ptr<SaltyBehaviour>>::const_iterator it = m_objects.begin(); it != m_objects.end(); it++)
			SaltyReflection<SaltyBehaviour>::CallGui(GameObjects(), (*it).get());
	}

	void Scene::CallCoroutines()
	{
		for (std::vector<std::unique_ptr<SaltyBehaviour>>::const_iterator it = m_objects.begin(); it != m_objects.end(); it++)
			(*it)->CallCoroutines();
	}

	void Scene::Clear()
	{
		m_objects.clear();
		while (!m_init.empty())
			m_init.pop();
	}
	void Scene::operator<<(SaltyBehaviour *gameobj)
	{
		m_objects.push_back(std::unique_ptr<SaltyBehaviour>(gameobj));
		m_init.emplace(m_objects.size() - 1);
	}
}

std::ostream & operator<<(std::ostream &os, SaltyEngine::Scene &scene)
{
	os << "Scene " << scene.GetName() << " :" << std::endl;
	return (os);
}

