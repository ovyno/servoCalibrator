#include "servodata.h"

ServoData::ServoData(QObject *parent) : QObject(parent)
  , m_on(false)
  , m_currentServo(0)
  , m_socket(new QTcpSocket(this))
  , m_adapterNumber(0)
  , m_portNumber(0)
  , m_currentData(MIN_SERVO_VALUE)
{

}

bool ServoData::Connect(QString ip)
{
    // m_socket = new QTcpSocket();
    m_socket->connectToHost(ip, 1234);
    QObject::connect(m_socket,SIGNAL(readyRead()),this,SLOT(ReadTCPData()));
    return m_socket->waitForConnected();
}

void ServoData::SetAdapterAndPort()
{
    QString str;
    str=QString("p%1:%2:%3\r\n").arg(m_currentServo).arg(m_adapterNumber).arg(m_portNumber);
    // QByteArray arr(str);
    m_socket->write(str.toStdString().c_str());
    m_socket->flush();
}

void ServoData::GetDataForServo()
{
    qDebug() << "GetDataForServo";
    // need to read adapter port and pin  #px
    QString str;
    str=QString("p%1\r\n").arg(m_currentServo);
    m_socket->write(str.toStdString().c_str());
    m_socket->flush();

    str=QString("s%1\r\n").arg(m_currentServo);
    m_socket->write(str.toStdString().c_str());
    m_socket->flush();

    str=QString("o%1\r\n").arg(m_currentServo);
    m_socket->write(str.toStdString().c_str());
    m_socket->flush();

    str=QString("c%1\r\n").arg(m_currentServo);
    m_socket->write(str.toStdString().c_str());
    m_socket->flush();
    // need to read calibration data #cx

    // need to read raw data #px
}

void ServoData::AngleInc()
{
    if(m_currentData<MAX_SERVO_VALUE)
        setCurrentData(m_currentData+1);
}

void ServoData::AngleDec()
{
    if(m_currentData>MIN_SERVO_VALUE)
        setCurrentData(m_currentData-1);
}

void ServoData::SendRawData()
{
    QString str;
    str=QString("s%1:%2\r\n").arg(m_currentServo).arg(m_currentData);
    m_socket->write(str.toStdString().c_str());
    m_socket->flush();
}

void ServoData::SendCalibrationData()
{
    QString str;
    str=QString("c%1:%2:%3:%4:%5\r\n").arg(m_currentServo).arg(m_firstAngle).arg(m_firstData).arg(m_secondAngle).arg(m_secondData);
    m_socket->write(str.toStdString().c_str());
    m_socket->flush();
}

void ServoData::UpdateOnOff()
{
    QString str;
    str=QString("o%1:%2\r\n").arg(m_currentServo).arg(m_on);
    m_socket->write(str.toStdString().c_str());
    m_socket->flush();
}

void ServoData::ReadCurrentServo()
{

}

bool ServoData::on() const
{
    return m_on;
}

int ServoData::adapterNumber() const
{
    return m_adapterNumber;
}

int ServoData::portNumber() const
{
    return m_portNumber;
}

int ServoData::currentAngle() const
{
    return m_currentAngle;
}

int ServoData::currentData() const
{
    return m_currentData;
}

int ServoData::firstData() const
{
    return m_firstData;
}

int ServoData::secondData() const
{
    return m_secondData;
}

int ServoData::firstAngle() const
{
    return m_firstAngle;
}

int ServoData::secondAngle() const
{
    return m_secondAngle;
}

int ServoData::currentServo() const
{
    return m_currentServo;
}

void ServoData::ReadTCPData()
{
    QByteArray data = m_socket->readAll();
    QString str;
    str=data.data();
    qDebug()<<"ReadTCPData ";
    qDebug()<< str;


    QStringList messages = str.split("\r\n");
    for(int j=0;j<messages.size();++j)
    {
        QString command=messages[j].left(1);
        messages[j].remove(0,1);
        QStringList params=messages[j].split(":");

        qDebug()<<"Command:"<<command;
        for(int i=0;i<params.size();++i)
            qDebug()<<"params: "<<params[i];

        if(command=="p")
        {
            setAdapterNumber(params[1].toInt());
            setPortNumber(params[2].toInt());
        }
        if(command=="o")
        {
            setOn(params[1].toInt());
        }
        if(command=="s")
        {
            setCurrentData(params[1].toInt());
        }
        if(command=="c")
        {
            setFirstAngle(params[1].toInt());
            setFirstData(params[2].toInt());
            setSecondAngle(params[3].toInt());
            setSecondData(params[4].toInt());
        }
    }
}

void ServoData::setOn(bool on)
{
    if (m_on == on)
        return;

    m_on = on;
    emit onChanged(on);
}

void ServoData::setAdapterNumber(int adapterNumber)
{
    if (m_adapterNumber == adapterNumber)
        return;

    m_adapterNumber = adapterNumber;
    emit adapterNumberChanged(adapterNumber);
}

void ServoData::setPortNumber(int portNumber)
{
    if (m_portNumber == portNumber)
        return;

    m_portNumber = portNumber;
    emit portNumberChanged(portNumber);
}

void ServoData::setCurrentAngle(int currentAngle)
{
    if (m_currentAngle == currentAngle)
        return;

    m_currentAngle = currentAngle;
    emit currentAngleChanged(currentAngle);
}

void ServoData::setCurrentData(int currentData)
{
    if (m_currentData == currentData)
        return;

    m_currentData = currentData;
    emit currentDataChanged(currentData);
    SendRawData();
}

void ServoData::setFirstData(int firstData)
{
    if (m_firstData == firstData)
        return;

    m_firstData = firstData;
    emit firstDataChanged(firstData);
}

void ServoData::setSecondData(int secondData)
{
    if (m_secondData == secondData)
        return;

    m_secondData = secondData;
    emit secondDataChanged(secondData);

}

void ServoData::setFirstAngle(int firstAngle)
{
    if (m_firstAngle == firstAngle)
        return;

    m_firstAngle = firstAngle;
    emit firstAngleChanged(firstAngle);
}

void ServoData::setSecondAngle(int secondAngle)
{
    if (m_secondAngle == secondAngle)
        return;

    m_secondAngle = secondAngle;
    emit secondAngleChanged(secondAngle);
}

void ServoData::setCurrentServo(int currentServo)
{
    if (m_currentServo == currentServo)
        return;

    m_currentServo = currentServo;
    emit currentServoChanged(currentServo);
    GetDataForServo();
}

