#ifndef EVENT_RECEIVER_CLASS_H
#define EVENT_RECEIVER_CLASS_H
#include <irrlicht.h>
// Event receiver
class AloneBowling;
class EventReceiverClass : public irr::IEventReceiver  {
private:
  AloneBowling* game_;
  irr::IrrlichtDevice* dev_;
public:
  EventReceiverClass(AloneBowling*, irr::IrrlichtDevice*);
	virtual bool OnEvent(const irr::SEvent &TEvent);
};
#endif
