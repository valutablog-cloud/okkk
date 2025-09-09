#include <QtCore/QObject>
#include <QtWebSockets/QWebSocket>
#include <qtimer.h>

#include "config.h"

class WebSocketClient : public QObject
{
	Q_OBJECT
public:
	WebSocketClient(QObject*, int);
	~WebSocketClient();

private slots:
	void tick();	
	void check();
	void delayed();
	void onConnected();
	void onDisconnected();
	void onError(QAbstractSocket::SocketError error);
	void onTextMessageReceived(QString message);
	bool ParseMessage(std::vector<char> &msg, std::pair<std::string, std::string> &out);

private:
	QWebSocket m_webSocket;
	bool disconnected;
	bool connected;
	QObject *parent;
	QTimer timer;
	QTimer timer_c;
	QTimer delayed_;

	static int current_port;
};