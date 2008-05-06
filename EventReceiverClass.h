#include <irrlicht/irrlicht.h>
// Event receiver
class EventReceiverClass : public irr::IEventReceiver  {

public:

	virtual bool OnEvent(const irr::SEvent &TEvent);
};
