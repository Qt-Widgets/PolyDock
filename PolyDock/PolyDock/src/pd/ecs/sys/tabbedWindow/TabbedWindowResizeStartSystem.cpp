#include <pd/pch/PCH.h>
#include <pd/ecs/sys/tabbedWindow/TabbedWindowResizeStartSystem.hpp>

#include <pd/ecs/cmp/root/InputComponent.hpp>
#include <pd/ecs/cmp/tabbedWindow/TabbedWindowResizeHoverComponent.hpp>
#include <pd/ecs/cmp/tabbedWindow/TabbedWindowResizeActiveComponent.hpp>

using namespace ::pd::ecs::sys::tabbedWindow;
using namespace ::pd::ecs::cmp::tabbedWindow;
using namespace ::pd::ecs::cmp::root;
using namespace ::Eigen;

// ---------------------------------------------------------------------------------------------------------
void TabbedWindowResizeStartSystem::update(entt::registry& registry, entt::entity root) const
{
	auto view = registry.view<TabbedWindowResizeHoverComponent>();
	
	if (const auto* inputComponent = registry.try_get<InputComponent>(root))
	{
		if (inputComponent->wasJustPressed(InputComponent::eMouseButton::LEFT))
		{
			for (auto entity : view)
			{
				const auto& hoverCmp = view.get<TabbedWindowResizeHoverComponent>(entity);
				auto& activeCmp = registry.get_or_assign<TabbedWindowResizeActiveComponent>(entity);
				activeCmp.horizontal = hoverCmp.horizontal;
				activeCmp.vertical = hoverCmp.vertical;
			}
		}
	}
}