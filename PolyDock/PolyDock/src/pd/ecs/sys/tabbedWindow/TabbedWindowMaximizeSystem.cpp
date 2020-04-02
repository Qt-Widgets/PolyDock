#include <pd/pch/PCH.h>
#include <pd/ecs/sys/tabbedWindow/TabbedWindowMaximizeSystem.hpp>

#include <pd/ecs/cmp/tabbedWindow/TabbedWindowComponent.hpp>
#include <pd/ecs/cmp/tabbedWindow/TabbedWindowWidgetComponent.hpp>
#include <pd/ecs/cmp/tabbedWindow/TabbedWindowMaximizeRequestComponent.hpp>
#include <pd/ecs/cmp/tabbedWindowControl/Component.hpp>

using namespace ::pd::ecs::sys::tabbedWindow;
using namespace ::pd::ecs::cmp::tabbedWindow;
using namespace ::pd::ecs::cmp::tabbedWindowControl;

// ---------------------------------------------------------------------------------------------------------
void TabbedWindowMaximizeSystem::update(entt::registry& registry, entt::entity root) const
{
	auto view = registry.view<
		TabbedWindowComponent,
		TabbedWindowWidgetComponent,
		TabbedWindowMaximizeRequestComponent,
		Component>();

	for (auto entity : view)
	{
		auto& widgetCmp = view.get<TabbedWindowWidgetComponent>(entity);
		auto& controlCmp = view.get<Component>(entity);

		widgetCmp.window->getWidget()->showMaximized();
		controlCmp.maximized = true;

		registry.remove<TabbedWindowMaximizeRequestComponent>(entity);
	}
}