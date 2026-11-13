#include "EventManager.hh"

void EventManager::addHandler(OnEvent event)
{
	handlers.push_back(event);
}

void EventManager::trigger(GameEvent* event)
{
	std::for_each(handlers.begin(), handlers.end(), [&event](OnEvent& handler)
		{
			handler(event);

		});
}
