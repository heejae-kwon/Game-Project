#include "BaseComponent.hpp"

Component::BaseComponent::BaseComponent(Actor* owner_) : m_hashId(0), m_type(Type::TYPE_LENGTH), m_owner(owner_), m_isActive(true) {}


