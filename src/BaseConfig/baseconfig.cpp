#include "baseconfig.h"
#include <QVariant>

BaseConfig::BaseConfig(QObject *parent) : QGSettings(GSCHEMA, GSPATH, parent)
{
    m_locations = QStringList() 
        << "TopLeft"
        << "TopCenter"
        << "TopRight"
        << "Left"
        << "Center"
        << "Right"
        << "BottomLeft"
        << "BottomCenter"
        << "BottomRight";
}

QString BaseConfig::Path()
{
    return get(KEY_Path).toString();
}

void BaseConfig::setPath(QString path)
{
    set(KEY_Path, path);
}

int BaseConfig::Timeout()
{
    return get(KEY_Timeout).toInt();
}

void BaseConfig::setTimeout(int timeout)
{
    set(KEY_Timeout, timeout);
}

bool BaseConfig::Visible()
{
    return get(KEY_Visible).toBool();
}

void BaseConfig::setVisible(bool visible)
{
    set(KEY_Visible, visible);
}

QString BaseConfig::Location()
{
    return get(KEY_Location).toString();
}

void BaseConfig::setLocation(QString location)
{
    set(KEY_Visible, location);
}

QString BaseConfig::Color()
{
    return get(KEY_Color).toString();
}

void BaseConfig::setColor(QString color)
{
    set(KEY_Color, color);
}

int BaseConfig::ShadowDeep()
{
    return get(KEY_ShadowDeep).toInt();
}

void BaseConfig::setShadowDeep(int shadowdeep)
{
    set(KEY_ShadowDeep, shadowdeep);
}

int BaseConfig::shadowBlur()
{
    return get(KEY_shadowBlur).toInt();
}

void BaseConfig::setshadowBlur(int shadowblur)
{
    set(KEY_shadowBlur, shadowblur);
}

int BaseConfig::LocationToIndex(QString location)
{
    return m_locations.indexOf(location);
}

QString BaseConfig::LocationIndexToString(int index)
{
    return m_locations.at(index);
}
