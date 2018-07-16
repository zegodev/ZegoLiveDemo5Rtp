#pragma once

#include <iostream>
#include <QString>
#include <QVector>

struct deviceConfig
{
    QString deviceId;
    QString deviceName;
};


QVector< deviceConfig > GetAudioDevicesWithOSX();

QVector< deviceConfig >  GetVideoDevicesWithOSX();
