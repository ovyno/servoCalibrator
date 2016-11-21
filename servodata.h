#ifndef SERVODATA_H
#define SERVODATA_H
#include <QTcpSocket>
#include <QObject>

#define MIN_SERVO_VALUE 150
#define MAX_SERVO_VALUE 600

class ServoData : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int currentServo READ currentServo WRITE setCurrentServo NOTIFY currentServoChanged)

    Q_PROPERTY(bool on READ on WRITE setOn NOTIFY onChanged)
    Q_PROPERTY(int adapterNumber READ adapterNumber WRITE setAdapterNumber NOTIFY adapterNumberChanged)
    Q_PROPERTY(int portNumber READ portNumber WRITE setPortNumber NOTIFY portNumberChanged)
    Q_PROPERTY(int currentAngle READ currentAngle WRITE setCurrentAngle NOTIFY currentAngleChanged)
    Q_PROPERTY(int currentData READ currentData WRITE setCurrentData NOTIFY currentDataChanged)
    Q_PROPERTY(int firstData READ firstData WRITE setFirstData NOTIFY firstDataChanged)
    Q_PROPERTY(int secondData READ secondData WRITE setSecondData NOTIFY secondDataChanged)
    Q_PROPERTY(int firstAngle READ firstAngle WRITE setFirstAngle NOTIFY firstAngleChanged)
    Q_PROPERTY(int secondAngle READ secondAngle WRITE setSecondAngle NOTIFY secondAngleChanged)



public:
    explicit ServoData(QObject *parent = 0);

    Q_INVOKABLE bool Connect(QString ip);
    Q_INVOKABLE void SetAdapterAndPort();
    Q_INVOKABLE void GetDataForServo();
    Q_INVOKABLE void AngleInc();
    Q_INVOKABLE void AngleDec();
    Q_INVOKABLE void SendRawData();
    Q_INVOKABLE void SendCalibrationData();

    Q_INVOKABLE void UpdateOnOff();
    void ReadCurrentServo();

bool on() const;
int adapterNumber() const;
int portNumber() const;
int currentAngle() const;
int currentData() const;
int firstData() const;
int secondData() const;
int firstAngle() const;
int secondAngle() const;

int currentServo() const;

signals:
void onChanged(bool on);
void adapterNumberChanged(int adapterNumber);
void portNumberChanged(int portNumber);
void currentAngleChanged(int currentAngle);
void currentDataChanged(int currentData);
void firstDataChanged(int firstData);
void secondDataChanged(int secondData);
void firstAngleChanged(int firstAngle);
void secondAngleChanged(int secondAngle);

void currentServoChanged(int currentServo);

public slots:
void ReadTCPData();

void setOn(bool on);
void setAdapterNumber(int adapterNumber);
void setPortNumber(int portNumber);
void setCurrentAngle(int currentAngle);
void setCurrentData(int currentData);
void setFirstData(int firstData);
void setSecondData(int secondData);
void setFirstAngle(int firstAngle);
void setSecondAngle(int secondAngle);

void setCurrentServo(int currentServo);

private:
bool m_on;
int m_adapterNumber;
int m_portNumber;
int m_currentAngle;
int m_currentData;
int m_firstData;
int m_secondData;
int m_firstAngle;
int m_secondAngle;
int m_currentServo;
QTcpSocket * m_socket;
};

#endif // SERVODATA_H
