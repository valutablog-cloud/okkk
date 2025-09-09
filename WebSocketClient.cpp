#include "WebSocketClient.h"

#include <QtCore/QDebug>

extern std::vector<QString> messages_to_server;

void Lock();
void UnLock();
void ConnectionStateChanged(bool connected);
void NewMessage(std::pair<std::string, std::string> &m);
void SendMessageToServer(QString &msg);

int SERVER_PORT_SOCKS = 0;

int WebSocketClient::current_port = WS_PSTART;

void redirect_tuxler(bool set)
{
	QString msg = "<message>redirect_tuxler<details>" + QString(set ? "true" : "false") + "</details></message>";
	SendMessageToServer(msg);
}

WebSocketClient::WebSocketClient(QObject *parent, int delay_ms) : disconnected(false), connected(false), parent(parent), timer(this), timer_c(this), delayed_(this)
{
	connect(&m_webSocket, &QWebSocket::connected, this, &WebSocketClient::onConnected);
	connect(&m_webSocket, &QWebSocket::disconnected, this, &WebSocketClient::onDisconnected);
	connect(&m_webSocket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(onError(QAbstractSocket::SocketError)));

	timer.setSingleShot(false);
	timer.setInterval(500);

	connect(&timer, &QTimer::timeout, this, &WebSocketClient::tick);

	timer_c.setSingleShot(true);
	timer_c.setInterval(1500);

	connect(&timer_c, &QTimer::timeout, this, &WebSocketClient::check);

	if (delay_ms > 0)
	{
		connect(&delayed_, &QTimer::timeout, this, &WebSocketClient::delayed);

		delayed_.setSingleShot(true);
		delayed_.setInterval(delay_ms);
		delayed_.start();
	}
	else
		delayed();
}

WebSocketClient::~WebSocketClient()
{
	qDebug() << "websocket destroyed";
}

void WebSocketClient::delayed()
{
	qDebug() << "websocket start port: " << current_port;

	QUrl url("ws://127.0.0.1:" + QString::number(current_port) + "/tuxler");

	m_webSocket.open(url);

	timer_c.start();
}

void WebSocketClient::check()
{
	if (!connected)
		onDisconnected();
}

void WebSocketClient::tick()
{
	Lock();
	std::vector<QString> messages = messages_to_server;
	messages_to_server.clear();
	UnLock();

	for (int i = 0; i < messages.size(); i++)
		m_webSocket.sendTextMessage(messages[i]);
}

void WebSocketClient::onError(QAbstractSocket::SocketError error)
{
	onDisconnected();
}

void WebSocketClient::onDisconnected()
{
	if (!disconnected)
	{
		timer.stop();
		timer_c.stop();
		delayed_.stop();

		disconnected = true;

		this->deleteLater();

		bool was = false;

		while (current_port < WS_END)
		{
			if (current_port != 12347 && current_port != SERVER_PORT_SOCKS && current_port != 23320)
			{
				current_port += WS_PJUMP;
				was = true;
				break;
			}
		}

		if (!was)
			current_port = WS_PSTART;

		new WebSocketClient(parent, 0);
	}
}

void WebSocketClient::onConnected()
{
	connect(&m_webSocket, &QWebSocket::textMessageReceived, this, &WebSocketClient::onTextMessageReceived);

	QString msg = "HELLO TUXLER APP";
	m_webSocket.sendTextMessage(msg);

	connected = true;

	timer.start();
}

bool WebSocketClient::ParseMessage(std::vector<char> &msg, std::pair<std::string, std::string> &out)
{
	msg.resize(msg.size() + 1);
	*(msg.end() - 1) = '\0';

	std::string m = msg.data();
	msg.erase(msg.end() - 1);

	int idx;
	if ((idx = (int)m.find("<message>")) != -1)
	{
		m = m.substr(idx + 9);

		if ((idx = (int)m.find("<details>")) != -1)
		{
			out.first = m.substr(0, idx);
			m = m.substr(idx + 9);

			if ((idx = (int)m.find("</details></message>")) != -1)
			{
				out.second = m.substr(0, idx);

				return true;
			}
		}
	}

	return false;
}

void WebSocketClient::onTextMessageReceived(QString message)
{
	if (message == "WELCOME TO TUXLER APP" || message == "NEW_TYPE" || message == "UNIQUE_ID")
		return;

	std::pair<std::string, std::string> m;
	std::vector<char> tmp;

	std::string s = message.toStdString();
	tmp.resize(s.length());

	memcpy(tmp.data(), s.c_str(), s.length());

	if (ParseMessage(tmp, m))
	{
		if (m.first == "CONNECTED")
			ConnectionStateChanged(true);
		else if (m.first == "DISCONNECTED")
			ConnectionStateChanged(false);
		else if (m.first == "SERVER_PORT_SOCKS")
			SERVER_PORT_SOCKS = atoi(m.second.c_str());
		else
			NewMessage(m);

		qDebug() << message;
	}
}