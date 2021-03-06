#pragma once
#include "ECSBase.h"
#include <unordered_map>


namespace SemperEngine
{
	namespace ECS
	{
		class World;

		class WorldIterator
		{
		public:
			template<typename T>
			WorldIterator(T begin) :
				m_Position(begin)
			{
			}

			WorldIterator &operator++()
			{
				m_Position++;
				return *this;
			}

			WorldIterator &operator++(int)
			{
				WorldIterator iterator = *this;
				++(*this);
				return iterator;
			}

			bool operator!=(const WorldIterator &other)
			{
				return m_Position != other.m_Position;
			}

			WorldIterator &operator--()
			{
				m_Position--;
				return *this;
			}

			WorldIterator &operator--(int)
			{
				WorldIterator iterator = *this;
				--(*this);
				return iterator;
			}

			const EntityHandle &operator *() const
			{
				return (*m_Position).first;
			}

		private:
			Internal::EntityIterator m_Position;
		};
	}
}