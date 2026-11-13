#include "CollisionManager.hh"

void CollisionManager::addHandler(OnColEvent event)
{
	handlers.push_back(event);
}

void CollisionManager::trigger(CollisionEvent* event)
{
	std::for_each(handlers.begin(), handlers.end(), [&event](OnColEvent& handler)
		{
			handler(event);

		});
}
