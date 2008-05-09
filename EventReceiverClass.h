#ifndef EVENTRECEIVERCLASS_H
#define EVENTRECEIVERCLASS_H
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
