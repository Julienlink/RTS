#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_RTS.h"

class RTS : public QMainWindow
{
    Q_OBJECT

public:
    RTS(QWidget *parent = nullptr);
    ~RTS();

private:
    Ui::RTSClass ui;
};

