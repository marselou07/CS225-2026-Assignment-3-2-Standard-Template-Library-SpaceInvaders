#include "PlayerEventManager.hh"

void PlayerEventManager::addHandler(OnMoveEvent event)
{
	handlers.push_back(event);
}

void PlayerEventManager::trigger(MoveEvent* event)
{
	std::for_each(handlers.begin(), handlers.end(), [&event](OnMoveEvent& handler)
		{
			handler(event);

		});
}
