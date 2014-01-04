#ifndef QUsb_H
#define QUsb_H

#include <QObject>
#include <QDebug>
#include <compat.h>
// Include Windows headers
#include <windows.h>
#include <stdio.h>
#include <tchar.h>
#include <strsafe.h>

// Include WinUSB headers
#include <winusb.h>
#include <Usb100.h>
#include <Setupapi.h>

// Linked libraries
#pragma comment (lib , "setupapi.lib" )
#pragma comment (lib , "winusb.lib" )

/*
VID_0483&PID_FEDC
Device_GUID="{9f543223-cede-4fa3-b376-a25ce9a30e75}"
*/

static const GUID OSR_DEVICE_INTERFACE =
{ 0x9F543223, 0xCEDE, 0x4fa3, { 0xB3, 0x76, 0xA2, 0x5C, 0xE9, 0xA3, 0x0E, 0x75 } };

class QUsb : public QObject
{
    Q_OBJECT

    struct PIPE_ID
    {
        uchar  PipeInId;
        uchar  PipeOutId;
    };
public:
    explicit QUsb(QObject *parent = 0);
    ~QUsb();
    
public slots:
    qint32 open();
    void close();
    qint32 read(QByteArray *buf, quint32 bytes);
    qint32 write(QByteArray *buf, quint32 bytes);

private:
    bool GetDeviceHandle(GUID guidDeviceInterface, PHANDLE hDeviceHandle);
    bool GetWinUSBHandle(HANDLE hDeviceHandle, PWINUSB_INTERFACE_HANDLE phWinUSBHandle);
    bool GetUSBDeviceSpeed(WINUSB_INTERFACE_HANDLE hWinUSBHandle, quint8 *pDeviceSpeed);
    bool QueryDeviceEndpoints(WINUSB_INTERFACE_HANDLE hWinUSBHandle, PIPE_ID* pipeid);
    void PrintUsbError(const QString& func);

    GUID m_guidDeviceInterface;
    HANDLE m_devHandle;
    WINUSB_INTERFACE_HANDLE m_usbHandle;
    uchar m_devSpeed;
    PIPE_ID m_pipeId;
};

#endif // QUsb_H
