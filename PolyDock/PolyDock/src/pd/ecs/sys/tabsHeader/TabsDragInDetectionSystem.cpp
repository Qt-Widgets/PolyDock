#include <pd/pch/PCH.h>
#include <pd/ecs/sys/tabsHeader/TabsDragInDetectionSystem.hpp>

// in
#include <pd/ecs/cmp/root/InputComponent.hpp>
#include <pd/ecs/cmp/tabsHeader/HoveredTabComponent.hpp>
#include <pd/ecs/cmp/tabsHeader/TabsHeaderComponent.hpp>
#include <pd/ecs/cmp/tabsHeader/TabsHeaderWidgetComponent.hpp>
#include <pd/ecs/cmp/tabbedWindow/TabbedWindowMovementActiveComponent.hpp>
// out
#include <pd/ecs/cmp/tabsHeader/TabsDragInRequestComponent.hpp>

using namespace ::pd::ecs::sys::tabsHeader;
using namespace ::pd::ecs::cmp::tabbedWindow;
using namespace ::pd::ecs::cmp::tabsHeader;
using namespace ::pd::ecs::cmp::root;

// ---------------------------------------------------------------------------------------------------------
void TabsDragInDetectionSystem::update(entt::registry& registry, entt::entity root) const
{
	auto srcView = registry.view<TabbedWindowMovementActiveComponent, HoveredTabComponent>();
	auto dstView = registry.view<
		TabsHeaderWidgetComponent,
		TabsHeaderComponent
			>(entt::exclude<TabbedWindowMovementActiveComponent>);

	if (const auto* inputComponent = registry.try_get<InputComponent>(root))
	{
		for (auto source : srcView)
		{
			for (auto destination : dstView)
			{
				const auto& dstWidget = dstView.get<TabsHeaderWidgetComponent>(destination);
				const auto& dstHeader = dstView.get<TabsHeaderComponent>(destination);
				int dstPos = dstWidget.getTabIdxFromPosition(inputComponent->getCursorPos());

				if (dstPos == -1 && dstWidget.isPositionOnTheRightOfLastTab(inputComponent->getCursorPos()))
					dstPos = static_cast<int>(dstHeader.tabs.size());

				if (dstPos != -1 && dstWidget.getWidgetRect().contains(inputComponent->getCursorPos()))
					registry.assign<TabsDragInRequestComponent>(destination, source, dstPos);
			}
		}
	}
}