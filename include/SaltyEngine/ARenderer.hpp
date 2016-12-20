#pragma once

#ifndef ARENDERER_HPP_
#define ARENDERER_HPP_

#include <memory>
#include <map>
#include "SaltyEngine/IRenderer.hpp"
#include "SaltyEngine/ASpriteRenderer.hpp"
#include "SaltyEngine/Config.hpp"

namespace SaltyEngine
{
	class Scene;
	template <class T>
	class ARenderer : public IRenderer
	{
	public:
		typedef std::list<std::unique_ptr<ASpriteRenderer<T>>> SpriteList;
		typedef  std::map<int, SpriteList> SpriteMap;
	public:
		virtual ~ARenderer() {};
		void Display() const override = 0;

	private:
		static SpriteMap m_spriteRenderers;
	public:
		static void AddSpriteRenderer(ASpriteRenderer<T> *const sprr)
		{
			m_spriteRenderers.at(sprr->GetLayer()).push_back(std::unique_ptr<ASpriteRenderer<T>>(sprr));
		}

		static const SpriteMap &GetSprites()
		{
			return (m_spriteRenderers);
		}

		virtual ::SaltyEngine::Vector2i GetRealSize() const = 0;
	};
}

#endif // !ARENDERER_HPP_
