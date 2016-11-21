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
		for (std::vector<std::unique_ptr<GameObject>>::const_iterator it = m_objects.begin(); it != m_objects.end(); it++)
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

	const std::unique_ptr<GameObject> &Scene::operator[](size_t index) const
	{
		return m_objects[index];
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
			std::list<SaltyBehaviour *> Sb = m_objects[m_init.front()]->GetComponents<SaltyBehaviour *>();
			for (std::list<SaltyBehaviour *>::const_iterator it = Sb.begin(); it != Sb.end(); it++)
			{
				SaltyReflection<SaltyBehaviour>::CallStart(GameObjects(), (*it));
			}
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
		for (std::vector<std::unique_ptr<GameObject>>::const_iterator obj = m_objects.begin(); obj != m_objects.end(); obj++)
		{
			std::list<SaltyBehaviour *> Sb = (*obj)->GetComponents<SaltyBehaviour *>();
			for (std::list<SaltyBehaviour *>::const_iterator it = Sb.begin(); it != Sb.end(); it++)
			{
				SaltyReflection<SaltyBehaviour>::CallUpdate(GameObjects(), (*it));
			}
		}
	}

	/**
	 * @fn	void Scene::FixedUpdate()
	 *
	 * @brief	Fixed update.
	 */

	void Scene::FixedUpdate()
	{
		for (std::vector<std::unique_ptr<GameObject>>::const_iterator obj = m_objects.begin(); obj != m_objects.end(); obj++)
		{
			std::list<SaltyBehaviour *> Sb = (*obj)->GetComponents<SaltyBehaviour *>();
			for (std::list<SaltyBehaviour *>::const_iterator it = Sb.begin(); it != Sb.end(); it++)
			{
				SaltyReflection<SaltyBehaviour>::CallFixedUpdate(GameObjects(), (*it));
			}
		}
	}

	/**
	 * @fn	void Scene::OnTriggerEnter()
	 *
	 * @brief	Executes the trigger enter action.
	 */

	void Scene::OnTriggerEnter()
	{
		for (std::vector<std::unique_ptr<GameObject>>::const_iterator obj = m_objects.begin(); obj != m_objects.end(); obj++)
		{
			std::list<SaltyBehaviour *> Sb = (*obj)->GetComponents<SaltyBehaviour *>();
			for (std::list<SaltyBehaviour *>::const_iterator it = Sb.begin(); it != Sb.end(); it++)
			{
				SaltyReflection<SaltyBehaviour>::CallOnTriggerEnter(GameObjects(), (*it));
			}
		}
	}

	/**
	 * @fn	void Scene::OnTriggerExit()
	 *
	 * @brief	Executes the trigger exit action.
	 */

	void Scene::OnTriggerExit()
	{
		for (std::vector<std::unique_ptr<GameObject>>::const_iterator obj = m_objects.begin(); obj != m_objects.end(); obj++)
		{
			std::list<SaltyBehaviour *> Sb = (*obj)->GetComponents<SaltyBehaviour *>();
			for (std::list<SaltyBehaviour *>::const_iterator it = Sb.begin(); it != Sb.end(); it++)
			{
				SaltyReflection<SaltyBehaviour>::CallOnTriggerExit(GameObjects(), (*it));
			}
		}
	}

	/**
	 * @fn	void Scene::OnTriggerStay()
	 *
	 * @brief	Executes the trigger stay action.
	 */

	void Scene::OnTriggerStay()
	{
		for (std::vector<std::unique_ptr<GameObject>>::const_iterator obj = m_objects.begin(); obj != m_objects.end(); obj++)
		{
			std::list<SaltyBehaviour *> Sb = (*obj)->GetComponents<SaltyBehaviour *>();
			for (std::list<SaltyBehaviour *>::const_iterator it = Sb.begin(); it != Sb.end(); it++)
			{
				SaltyReflection<SaltyBehaviour>::CallOnTriggerStay(GameObjects(), (*it));
			}
		}
	}

	/**
	 * @fn	void Scene::OnCollisionEnter()
	 *
	 * @brief	Executes the collision enter action.
	 */

	void Scene::OnCollisionEnter()
	{
		for (std::vector<std::unique_ptr<GameObject>>::const_iterator obj = m_objects.begin(); obj != m_objects.end(); obj++)
		{
			std::list<SaltyBehaviour *> Sb = (*obj)->GetComponents<SaltyBehaviour *>();
			for (std::list<SaltyBehaviour *>::const_iterator it = Sb.begin(); it != Sb.end(); it++)
			{
				SaltyReflection<SaltyBehaviour>::CallOnCollisionEnter(GameObjects(), (*it));
			}
		}
	}

	/**
	 * @fn	void Scene::OnCollisionExit()
	 *
	 * @brief	Executes the collision exit action.
	 */

	void Scene::OnCollisionExit()
	{
		for (std::vector<std::unique_ptr<GameObject>>::const_iterator obj = m_objects.begin(); obj != m_objects.end(); obj++)
		{
			std::list<SaltyBehaviour *> Sb = (*obj)->GetComponents<SaltyBehaviour *>();
			for (std::list<SaltyBehaviour *>::const_iterator it = Sb.begin(); it != Sb.end(); it++)
			{
				SaltyReflection<SaltyBehaviour>::CallOnCollisionExit(GameObjects(), (*it));
			}
		}
	}

	/**
	 * @fn	void Scene::OnCollisionStay()
	 *
	 * @brief	Executes the collision stay action.
	 */

	void Scene::OnCollisionStay()
	{
		for (std::vector<std::unique_ptr<GameObject>>::const_iterator obj = m_objects.begin(); obj != m_objects.end(); obj++)
		{
			std::list<SaltyBehaviour *> Sb = (*obj)->GetComponents<SaltyBehaviour *>();
			for (std::list<SaltyBehaviour *>::const_iterator it = Sb.begin(); it != Sb.end(); it++)
			{
				SaltyReflection<SaltyBehaviour>::CallOnCollisionStay(GameObjects(), (*it));
			}
		}
	}

	/**
	 * @fn	void Scene::OnMouseEnter()
	 *
	 * @brief	Executes the mouse enter action.
	 */

	void Scene::OnMouseEnter()
	{
		for (std::vector<std::unique_ptr<GameObject>>::const_iterator obj = m_objects.begin(); obj != m_objects.end(); obj++)
		{
			std::list<SaltyBehaviour *> Sb = (*obj)->GetComponents<SaltyBehaviour *>();
			for (std::list<SaltyBehaviour *>::const_iterator it = Sb.begin(); it != Sb.end(); it++)
			{
				SaltyReflection<SaltyBehaviour>::CallOnMouseEnter(GameObjects(), (*it));
			}
		}
	}

	/**
	 * @fn	void Scene::OnMouseExit()
	 *
	 * @brief	Executes the mouse exit action.
	 */

	void Scene::OnMouseExit()
	{
		for (std::vector<std::unique_ptr<GameObject>>::const_iterator obj = m_objects.begin(); obj != m_objects.end(); obj++)
		{
			std::list<SaltyBehaviour *> Sb = (*obj)->GetComponents<SaltyBehaviour *>();
			for (std::list<SaltyBehaviour *>::const_iterator it = Sb.begin(); it != Sb.end(); it++)
			{
				SaltyReflection<SaltyBehaviour>::CallOnMouseExit(GameObjects(), (*it));
			}
		}
	}

	/**
	 * @fn	void Scene::OnMouseOver()
	 *
	 * @brief	Executes the mouse over action.
	 */

	void Scene::OnMouseOver()
	{
		for (std::vector<std::unique_ptr<GameObject>>::const_iterator obj = m_objects.begin(); obj != m_objects.end(); obj++)
		{
			std::list<SaltyBehaviour *> Sb = (*obj)->GetComponents<SaltyBehaviour *>();
			for (std::list<SaltyBehaviour *>::const_iterator it = Sb.begin(); it != Sb.end(); it++)
			{
				SaltyReflection<SaltyBehaviour>::CallOnMouseOver(GameObjects(), (*it));
			}
		}
	}

	/**
	 * @fn	void Scene::OnGui()
	 *
	 * @brief	Executes the graphical user interface action.
	 */

	void Scene::OnGui()
	{
		for (std::vector<std::unique_ptr<GameObject>>::const_iterator obj = m_objects.begin(); obj != m_objects.end(); obj++)
		{
			std::list<SaltyBehaviour *> Sb = (*obj)->GetComponents<SaltyBehaviour *>();
			for (std::list<SaltyBehaviour *>::const_iterator it = Sb.begin(); it != Sb.end(); it++)
			{
				SaltyReflection<SaltyBehaviour>::CallGui(GameObjects(), (*it));
			}
		}
	}

	/**
	 * @fn	void Scene::CallCoroutines()
	 *
	 * @brief	Call coroutines.
	 */

	void Scene::CallCoroutines()
	{
		for (std::vector<std::unique_ptr<GameObject>>::const_iterator obj = m_objects.begin(); obj != m_objects.end(); obj++)
		{
			std::list<SaltyBehaviour *> Sb = (*obj)->GetComponents<SaltyBehaviour *>();
			for (std::list<SaltyBehaviour *>::const_iterator it = Sb.begin(); it != Sb.end(); it++)
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

	void Scene::operator<<(GameObject *gameobj)
	{
		m_objects.push_back(std::unique_ptr<GameObject>(gameobj));
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

std::ostream & operator<<(std::ostream &os, SaltyEngine::Scene &scene)
{
	os << "Scene " << scene.GetName() << " :" << std::endl;
	return (os);
}
