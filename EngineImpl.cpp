#include <qstring.h>
#include <qobject.h>

#include <WebSocketClient.h>

void StartWebSocketClient(QObject *parent)
{
	new WebSocketClient(parent, 3000);
}

