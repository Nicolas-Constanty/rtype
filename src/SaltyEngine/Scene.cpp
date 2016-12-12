#include "SaltyEngine/AScene.hpp"
#include "SaltyEngine/Debug.hpp"

namespace SaltyEngine
{
	/**
	 * @fn	AScene::AScene()
	 *
	 * @brief	Default constructor.
	 */

	AScene::AScene() : Object("AScene")
	{
		m_gravity = 9.81f;
	}

	AScene::AScene(const std::string &name) : Object(name) {
		m_gravity = 9.81f;
	}

	/**
	 * @fn	AScene::~AScene()
	 *
	 * @brief	Destructor.
	 */

	AScene::~AScene()
	{
	}
	
	/**
	 * @fn	size_t AScene::GetSize() const
	 *
	 * @brief	Gets the size.
	 *
	 * @return	The size.
	 */

	size_t AScene::GetSize(void) const
	{
		return (m_objects.size());
	}

	float AScene::GetGravity(void) const
	{
		return (m_gravity);
	}

	void AScene::SetGravity(float gravity)
	{
		m_gravity = gravity;
	}

	/**
	 * @fn	std::ostream &AScene::print(std::ostream &os) const
	 *
	 * @brief	Prints the given operating system.
	 *
	 * @param [in,out]	os	The operating system.
	 *
	 * @return	A reference to a std::ostream.
	 */

	std::ostream &AScene::print(std::ostream &os) const
	{
		for (std::vector<GameObject*>::const_iterator it = m_objects.begin(); it != m_objects.end(); ++it)
		{
			os << "\t" << (**it) << std::endl;
		}
		return (os);
	}

	/**
	 * @fn	const std::unique_ptr<SaltyBehaviour> &AScene::operator[](size_t index) const
	 *
	 * @brief	Array indexer operator.
	 *
	 * @param	index	Zero-based index of the.
	 *
	 * @return	The indexed value.
	 */

    GameObject const &AScene::operator[](size_t index) const
	{
		return *m_objects[index];
	}

	/**
	 * @fn	void AScene::OnStart()
	 *
	 * @brief	Executes the start action.
	 */

	void AScene::OnStart()
	{

		while (!m_init.empty())
		{
			const std::list<SaltyBehaviour *> &Sb = m_objects[m_init.front()]->GetSaltyBehaviour();
			for (std::list<SaltyBehaviour *>::const_iterator it = Sb.begin(); it != Sb.end(); ++it)
				if ((*it)->enabled)
					(*it)->Start();
			m_init.pop();
		}
	}

	/**
	 * @fn	void AScene::Update()
	 *
	 * @brief	Updates objects in scene.
	 */

	void AScene::Update()
	{
		std::vector<GameObject*> objects = m_objects;
		for (std::vector<GameObject*>::const_iterator obj = objects.begin(); obj != objects.end(); ++obj)
		{
			const std::list<SaltyBehaviour *> &Sb = (*obj)->GetSaltyBehaviour();
			for (std::list<SaltyBehaviour *>::const_iterator it = Sb.begin(); it != Sb.end(); ++it)
				if ((*it)->enabled)
					(*it)->Update();
		}
	}

	/**
	 * @fn	void AScene::FixedUpdate()
	 *
	 * @brief	Fixed update.
	 */

	void AScene::FixedUpdate()
	{
		std::vector<GameObject*> objects = m_objects;
		for (std::vector<GameObject*>::const_iterator obj = objects.begin(); obj != objects.end(); ++obj)
		{
			const std::list<SaltyBehaviour *> &Sb = (*obj)->GetSaltyBehaviour();
			for (std::list<SaltyBehaviour *>::const_iterator it = Sb.begin(); it != Sb.end(); ++it)
				if ((*it)->enabled)
					(*it)->FixedUpdate();
		}
	}

	/**
	 * @fn	void AScene::OnTriggerEnter()
	 *
	 * @brief	Executes the trigger enter action.
	 */

	void AScene::OnTriggerEnter()
	{
		while (!m_onTriggerEnter.empty())
		{
			m_onTriggerEnter.front()();
			m_onTriggerEnter.pop();
		}
	}

	/**
	 * @fn	void AScene::OnTriggerExit()
	 *
	 * @brief	Executes the trigger exit action.
	 */

	void AScene::OnTriggerExit()
	{
		while (!m_onTriggerExit.empty())
		{
			m_onTriggerExit.front()();
			m_onTriggerExit.pop();
		}
	}

	/**
	 * @fn	void AScene::OnTriggerStay()
	 *
	 * @brief	Executes the trigger stay action.
	 */

	void AScene::OnTriggerStay()
	{
		while (!m_onTriggerStay.empty())
		{
			m_onTriggerStay.front()();
			m_onTriggerStay.pop();
		}
	}

	/**
	 * @fn	void AScene::OnCollisionEnter()
	 *
	 * @brief	Executes the collision enter action.
	 */

	void AScene::OnCollisionEnter()
	{
		while (!m_onCollisionEnter.empty())
		{
			m_onCollisionEnter.front()();
			m_onCollisionEnter.pop();
		}
	}

	/**
	 * @fn	void AScene::OnCollisionExit()
	 *
	 * @brief	Executes the collision exit action.
	 */

	void AScene::OnCollisionExit()
	{
		while (!m_onCollisionExit.empty())
		{
			m_onCollisionExit.front()();
			m_onCollisionExit.pop();
		}
	}

	/**
	 * @fn	void AScene::OnCollisionStay()
	 *
	 * @brief	Executes the collision stay action.
	 */

	void AScene::OnCollisionStay()
	{
		while (!m_onCollisionStay.empty())
		{
			m_onCollisionStay.front()();
			m_onCollisionStay.pop();
		}
	}

	/**
	 * @fn	void AScene::OnMouseEnter()
	 *
	 * @brief	Executes the mouse enter action.
	 */

	void AScene::OnMouseEnter()
	{
		for (std::vector<GameObject*>::const_iterator obj = m_objects.begin(); obj != m_objects.end(); ++obj)
		{
			const std::list<SaltyBehaviour *> &Sb = (*obj)->GetSaltyBehaviour();
			for (std::list<SaltyBehaviour *>::const_iterator it = Sb.begin(); it != Sb.end(); ++it)
				if ((*it)->enabled)
					(*it)->OnMouseEnter();
		}
	}

	/**
	 * @fn	void AScene::OnMouseExit()
	 *
	 * @brief	Executes the mouse exit action.
	 */

	void AScene::OnMouseExit()
	{
		for (std::vector<GameObject*>::const_iterator obj = m_objects.begin(); obj != m_objects.end(); ++obj)
		{
			const std::list<SaltyBehaviour *> &Sb = (*obj)->GetSaltyBehaviour();
			for (std::list<SaltyBehaviour *>::const_iterator it = Sb.begin(); it != Sb.end(); ++it)
				if ((*it)->enabled)
					(*it)->OnMouseExit();
		}
	}

	/**
	 * @fn	void AScene::OnMouseOver()
	 *
	 * @brief	Executes the mouse over action.
	 */

	void AScene::OnMouseOver()
	{
		for (std::vector<GameObject*>::const_iterator obj = m_objects.begin(); obj != m_objects.end(); ++obj)
		{
			const std::list<SaltyBehaviour *> &Sb = (*obj)->GetSaltyBehaviour();
			for (std::list<SaltyBehaviour *>::const_iterator it = Sb.begin(); it != Sb.end(); ++it)
				if ((*it)->enabled)
					(*it)->OnMouseOver();
		}
	}

	/**
	 * @fn	void AScene::OnGui()
	 *
	 * @brief	Executes the graphical user interface action.
	 */

	void AScene::OnGui()
	{
		for (std::vector<GameObject*>::const_iterator obj = m_objects.begin(); obj != m_objects.end(); ++obj)
		{
			const std::list<SaltyBehaviour *> &Sb = (*obj)->GetSaltyBehaviour();
			for (std::list<SaltyBehaviour *>::const_iterator it = Sb.begin(); it != Sb.end(); ++it)
				if ((*it)->enabled)
					(*it)->OnGui();
		}
	}

	void AScene::OnDestroy()
	{
		for (std::vector<GameObject*>::const_iterator obj = m_objects.begin(); obj != m_objects.end(); ++obj)
		{
			const std::list<SaltyBehaviour *> &Sb = (*obj)->GetSaltyBehaviour();
			for (std::list<SaltyBehaviour *>::const_iterator it = Sb.begin(); it != Sb.end(); ++it)
				if ((*it)->enabled)
					(*it)->OnDestroy();
		}
	}

	/**
	 * @fn	void AScene::CallCoroutines()
	 *
	 * @brief	Call coroutines.
	 */

	void AScene::CallCoroutines()
	{
		for (std::vector<GameObject*>::const_iterator obj = m_objects.begin(); obj != m_objects.end(); ++obj)
		{
			const std::list<SaltyBehaviour *> &Sb = (*obj)->GetSaltyBehaviour();
			for (std::list<SaltyBehaviour *>::const_iterator it = Sb.begin(); it != Sb.end(); ++it)
			{
				if ((*it)->enabled)
					(*it)->CallCoroutines();
			}
		}
	}

	/**
	 * @fn	void AScene::Clear()
	 *
	 * @brief	Clears this object to its blank/initial state.
	 */

	void AScene::Clear()
	{
		m_objects.clear();
		while (!m_init.empty())
			m_init.pop();
	}

    /**
 * @fn	void AScene::operator<<(SaltyBehaviour *gameobj)
 *
 * @brief	Bitwise left shift operator.
 *
 * @param [in,out]	gameobj	If non-null, the gameobj.
 */

    void AScene::operator<<(GameObject * const gameobj)
    {
        if (gameobj == nullptr) {
            Debug::PrintWarning("AScene: Cannot add nullptr object");
            return;
        }
        m_objects.push_back(gameobj);
        m_init.emplace(m_objects.size() - 1);
    }

    GameObject *AScene::FindByName(std::string const &name) const
    {
		for (GameObject *curr : m_objects)
		{
			if (curr->GetName() == name)
				return curr;
		}
        return nullptr;
    }

    GameObject *AScene::FindById(size_t id) const
    {
		for (GameObject *curr : m_objects)
		{
			if (curr->GetInstanceID() == id)
				return curr;
		}
		return nullptr;
    }
}

/**
 * @fn	std::ostream & operator<<(std::ostream &os, SaltyEngine::AScene &scene)
 *
 * @brief	Stream insertion operator.
 *
 * @param [in,out]	os   	The operating system.
 * @param [in,out]	scene	The scene.
 *
 * @return	The shifted result.
 */

//std::ostream & operator<<(std::ostream &os, SaltyEngine::AScene &scene)
//{
//	os << "AScene " << scene.GetName() << " :" << std::endl;
//	return (os);
//}
