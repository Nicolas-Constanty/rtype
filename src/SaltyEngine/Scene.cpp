#include <SaltyEngine/Debug.hpp>
#include "SaltyEngine/Scene.hpp"

namespace SaltyEngine
{
	/**
	 * @fn	Scene::Scene()
	 *
	 * @brief	Default constructor.
	 */

	Scene::Scene() : Object("Scene")
	{
	}

	Scene::Scene(const std::string &name) : Object(name) {}

	/**
	 * @fn	Scene::~Scene()
	 *
	 * @brief	Destructor.
	 */

	Scene::~Scene()
	{
	}
	
	/**
	 * @fn	size_t Scene::GetSize() const
	 *
	 * @brief	Gets the size.
	 *
	 * @return	The size.
	 */

	size_t Scene::GetSize() const
	{
		return (m_objects.size());
	}

	/**
	 * @fn	std::ostream &Scene::print(std::ostream &os) const
	 *
	 * @brief	Prints the given operating system.
	 *
	 * @param [in,out]	os	The operating system.
	 *
	 * @return	A reference to a std::ostream.
	 */

	std::ostream &Scene::print(std::ostream &os) const
	{
		for (std::vector<GameObject*>::const_iterator it = m_objects.begin(); it != m_objects.end(); ++it)
		{
			os << "\t" << (**it) << std::endl;
		}
		return (os);
	}

	/**
	 * @fn	const std::unique_ptr<SaltyBehaviour> &Scene::operator[](size_t index) const
	 *
	 * @brief	Array indexer operator.
	 *
	 * @param	index	Zero-based index of the.
	 *
	 * @return	The indexed value.
	 */

    GameObject const &Scene::operator[](size_t index) const
	{
		return *m_objects[index];
	}

	/**
	 * @fn	void Scene::OnStart()
	 *
	 * @brief	Executes the start action.
	 */

	void Scene::OnStart()
	{
		while (!m_init.empty())
		{
            std::cout <<  m_init.front() << std::endl;
			const std::list<SaltyBehaviour *> &Sb = m_objects[m_init.front()]->GetSaltyBehaviour();
			for (std::list<SaltyBehaviour *>::const_iterator it = Sb.begin(); it != Sb.end(); ++it)
				(*it)->Start();
			m_init.pop();
		}
	}

	/**
	 * @fn	void Scene::Update()
	 *
	 * @brief	Updates objects in scene.
	 */

	void Scene::Update()
	{
		for (std::vector<GameObject*>::const_iterator obj = m_objects.begin(); obj != m_objects.end(); ++obj)
		{
			const std::list<SaltyBehaviour *> &Sb = (*obj)->GetSaltyBehaviour();
			for (std::list<SaltyBehaviour *>::const_iterator it = Sb.begin(); it != Sb.end(); ++it)
				(*it)->Update();
		}
	}

	/**
	 * @fn	void Scene::FixedUpdate()
	 *
	 * @brief	Fixed update.
	 */

	void Scene::FixedUpdate()
	{
		for (std::vector<GameObject*>::const_iterator obj = m_objects.begin(); obj != m_objects.end(); ++obj)
		{
			const std::list<SaltyBehaviour *> &Sb = (*obj)->GetSaltyBehaviour();
			for (std::list<SaltyBehaviour *>::const_iterator it = Sb.begin(); it != Sb.end(); ++it)
				(*it)->FixedUpdate();
		}
	}

	/**
	 * @fn	void Scene::OnTriggerEnter()
	 *
	 * @brief	Executes the trigger enter action.
	 */

	void Scene::OnTriggerEnter()
	{
		for (std::vector<GameObject*>::const_iterator obj = m_objects.begin(); obj != m_objects.end(); ++obj)
		{
			const std::list<SaltyBehaviour *> &Sb = (*obj)->GetSaltyBehaviour();
			for (std::list<SaltyBehaviour *>::const_iterator it = Sb.begin(); it != Sb.end(); ++it)
				(*it)->OnTriggerEnter();
		}
	}

	/**
	 * @fn	void Scene::OnTriggerExit()
	 *
	 * @brief	Executes the trigger exit action.
	 */

	void Scene::OnTriggerExit()
	{
		for (std::vector<GameObject*>::const_iterator obj = m_objects.begin(); obj != m_objects.end(); ++obj)
		{
			const std::list<SaltyBehaviour *> &Sb = (*obj)->GetSaltyBehaviour();
			for (std::list<SaltyBehaviour *>::const_iterator it = Sb.begin(); it != Sb.end(); ++it)
				(*it)->OnTriggerExit();
		}
	}

	/**
	 * @fn	void Scene::OnTriggerStay()
	 *
	 * @brief	Executes the trigger stay action.
	 */

	void Scene::OnTriggerStay()
	{
		for (std::vector<GameObject*>::const_iterator obj = m_objects.begin(); obj != m_objects.end(); ++obj)
		{
			const std::list<SaltyBehaviour *> &Sb = (*obj)->GetSaltyBehaviour();
			for (std::list<SaltyBehaviour *>::const_iterator it = Sb.begin(); it != Sb.end(); ++it)
				(*it)->OnTriggerStay();
		}
	}

	/**
	 * @fn	void Scene::OnCollisionEnter()
	 *
	 * @brief	Executes the collision enter action.
	 */

	void Scene::OnCollisionEnter()
	{
		for (std::vector<GameObject*>::const_iterator obj = m_objects.begin(); obj != m_objects.end(); ++obj)
		{
			const std::list<SaltyBehaviour *> &Sb = (*obj)->GetSaltyBehaviour();
			for (std::list<SaltyBehaviour *>::const_iterator it = Sb.begin(); it != Sb.end(); ++it)
				(*it)->OnCollisionEnter();
		}
	}

	/**
	 * @fn	void Scene::OnCollisionExit()
	 *
	 * @brief	Executes the collision exit action.
	 */

	void Scene::OnCollisionExit()
	{
		for (std::vector<GameObject*>::const_iterator obj = m_objects.begin(); obj != m_objects.end(); ++obj)
		{
			const std::list<SaltyBehaviour *> &Sb = (*obj)->GetSaltyBehaviour();
			for (std::list<SaltyBehaviour *>::const_iterator it = Sb.begin(); it != Sb.end(); ++it)
				(*it)->OnCollisionExit();
		}
	}

	/**
	 * @fn	void Scene::OnCollisionStay()
	 *
	 * @brief	Executes the collision stay action.
	 */

	void Scene::OnCollisionStay()
	{
		for (std::vector<GameObject*>::const_iterator obj = m_objects.begin(); obj != m_objects.end(); ++obj)
		{
			const std::list<SaltyBehaviour *> &Sb = (*obj)->GetSaltyBehaviour();
			for (std::list<SaltyBehaviour *>::const_iterator it = Sb.begin(); it != Sb.end(); ++it)
				(*it)->OnCollisionStay();
		}
	}

	/**
	 * @fn	void Scene::OnMouseEnter()
	 *
	 * @brief	Executes the mouse enter action.
	 */

	void Scene::OnMouseEnter()
	{
		for (std::vector<GameObject*>::const_iterator obj = m_objects.begin(); obj != m_objects.end(); ++obj)
		{
			const std::list<SaltyBehaviour *> &Sb = (*obj)->GetSaltyBehaviour();
			for (std::list<SaltyBehaviour *>::const_iterator it = Sb.begin(); it != Sb.end(); ++it)
				(*it)->OnMouseEnter();
		}
	}

	/**
	 * @fn	void Scene::OnMouseExit()
	 *
	 * @brief	Executes the mouse exit action.
	 */

	void Scene::OnMouseExit()
	{
		for (std::vector<GameObject*>::const_iterator obj = m_objects.begin(); obj != m_objects.end(); ++obj)
		{
			const std::list<SaltyBehaviour *> &Sb = (*obj)->GetSaltyBehaviour();
			for (std::list<SaltyBehaviour *>::const_iterator it = Sb.begin(); it != Sb.end(); ++it)
				(*it)->OnMouseExit();
		}
	}

	/**
	 * @fn	void Scene::OnMouseOver()
	 *
	 * @brief	Executes the mouse over action.
	 */

	void Scene::OnMouseOver()
	{
		for (std::vector<GameObject*>::const_iterator obj = m_objects.begin(); obj != m_objects.end(); ++obj)
		{
			const std::list<SaltyBehaviour *> &Sb = (*obj)->GetSaltyBehaviour();
			for (std::list<SaltyBehaviour *>::const_iterator it = Sb.begin(); it != Sb.end(); ++it)
				(*it)->OnMouseOver();
		}
	}

	/**
	 * @fn	void Scene::OnGui()
	 *
	 * @brief	Executes the graphical user interface action.
	 */

	void Scene::OnGui()
	{
		for (std::vector<GameObject*>::const_iterator obj = m_objects.begin(); obj != m_objects.end(); ++obj)
		{
			const std::list<SaltyBehaviour *> &Sb = (*obj)->GetSaltyBehaviour();
			for (std::list<SaltyBehaviour *>::const_iterator it = Sb.begin(); it != Sb.end(); ++it)
				(*it)->OnGui();
		}
	}

	void Scene::OnDestroy()
	{
		for (std::vector<GameObject*>::const_iterator obj = m_objects.begin(); obj != m_objects.end(); ++obj)
		{
			const std::list<SaltyBehaviour *> &Sb = (*obj)->GetSaltyBehaviour();
			for (std::list<SaltyBehaviour *>::const_iterator it = Sb.begin(); it != Sb.end(); ++it)
				(*it)->OnDestroy();
		}
	}

	/**
	 * @fn	void Scene::CallCoroutines()
	 *
	 * @brief	Call coroutines.
	 */

	void Scene::CallCoroutines()
	{
		for (std::vector<GameObject*>::const_iterator obj = m_objects.begin(); obj != m_objects.end(); ++obj)
		{
			const std::list<SaltyBehaviour *> &Sb = (*obj)->GetSaltyBehaviour();
			for (std::list<SaltyBehaviour *>::const_iterator it = Sb.begin(); it != Sb.end(); ++it)
			{
				(*it)->CallCoroutines();
			}
		}
	}

	/**
	 * @fn	void Scene::Clear()
	 *
	 * @brief	Clears this object to its blank/initial state.
	 */

	void Scene::Clear()
	{
		m_objects.clear();
		while (!m_init.empty())
			m_init.pop();
	}

    /**
 * @fn	void Scene::operator<<(SaltyBehaviour *gameobj)
 *
 * @brief	Bitwise left shift operator.
 *
 * @param [in,out]	gameobj	If non-null, the gameobj.
 */

    void Scene::operator<<(GameObject * const gameobj)
    {
        if (gameobj == nullptr) {
            Debug::PrintWarning("Cannot add nullptr object");
            return;
        }
        m_objects.push_back(gameobj);
        m_init.emplace(m_objects.size() - 1);
    }
}

/**
 * @fn	std::ostream & operator<<(std::ostream &os, SaltyEngine::Scene &scene)
 *
 * @brief	Stream insertion operator.
 *
 * @param [in,out]	os   	The operating system.
 * @param [in,out]	scene	The scene.
 *
 * @return	The shifted result.
 */

//std::ostream & operator<<(std::ostream &os, SaltyEngine::Scene &scene)
//{
//	os << "Scene " << scene.GetName() << " :" << std::endl;
//	return (os);
//}
