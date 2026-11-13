#pragma once
#include "event.hh"
#include <functional>
#include <vector>
#include <string>
#include "AECore/inc/AEEngine.h"
enum Type { MoveRight, MoveLeft };
class MoveEvent : public Event
{
public:
	Type MoveType;
};

typedef std::function<void(MoveEvent* event)> OnMoveEvent;

class PlayerEventManager
{
protected:
	std::vector<OnMoveEvent> handlers;
public:
	void addHandler(OnMoveEvent event);
	void trigger(MoveEvent* event);

};
