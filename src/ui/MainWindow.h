#pragma once
#include <QLabel>
#include <QLineEdit>
#include <QMainWindow>
#include <QPushButton>
#include <core/AppTimer.h>

class MainWindow : public QMainWindow {
  Q_OBJECT

public:
  MainWindow(QWidget *parent = nullptr);

private slots:
  void updateTime(const QString &time);
  void updatePhase(bool isWork);

private:
  PomodoroTimer *timer;
  QLabel *timeLabel;
  QPushButton *startBtn;
  QPushButton *pauseBtn;
  QPushButton *resetBtn;
};
