#include "newipengineconnector.h"


NewIPEngineConnector::NewIPEngineConnector(QObject *parent)
	: QThread(parent), timer(this)
{
	connect(&timer, SIGNAL(timeout()), this, SLOT(loop()));
	timer.setInterval(10);
	timer.setSingleShot(false);
	timer.start();

	event = CreateEvent(NULL, false, false, NULL);
}

bool NewIPEngineConnector::WaitForEvent(int timeout_ms)
{
	return WaitForSingleObject(event, timeout_ms) == WAIT_OBJECT_0;
}

void NewIPEngineConnector::SetEvent()
{
	::SetEvent(event);
}

NewIPEngineConnector::~NewIPEngineConnector()
{
	CloseHandle(event);
}

void NewIPEngineConnector::loop()
{
	if (WaitForEvent(1000))
		emit NewEngineEvent();
}