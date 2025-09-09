#ifndef NEWIPENGINECONNECTOR_H
#define NEWIPENGINECONNECTOR_H

#include <QThread>
#include <qtimer.h>
#include <Windows.h>

class NewIPEngineConnector : public QThread
{
	Q_OBJECT

public:
	NewIPEngineConnector(QObject *parent);
	~NewIPEngineConnector();

	bool WaitForEvent(int timeout_ms);
	void SetEvent();

private:
	QTimer timer;
	HANDLE event;

signals:
	void NewEngineEvent();

private slots:
	void loop();
};

#endif // NEWIPENGINECONNECTOR_H
