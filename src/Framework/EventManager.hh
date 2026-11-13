#pragma once
#include "event.hh"
#include <functional>
#include <vector>
#include <string>
#include "AECore/inc/AEEngine.h"
enum Type { MoveRight, MoveLeft, Shoot };
class GameEvent : public Event
{
public:
	Type PlayerType;
};

typedef std::function<void(GameEvent* event)> OnEvent;

class EventManager
{
protected:
	std::vector<OnEvent> handlers;
public:
	void addHandler(OnEvent event);
	void trigger(GameEvent* event);

};
