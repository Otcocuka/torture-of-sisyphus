#pragma once
#include <QObject>
#include <QTimer>
#include <chrono>
#include <cstddef>

class PomodoroTimer : public QObject {
  Q_OBJECT

public:
  explicit PomodoroTimer(QObject *parent = nullptr);
  void start();
  void pause();
  void reset();
  void setWorkMinutes(double mins);
  void setShortBreakMinutes(double mins);
  void setLongBreakMinutes(double mins);
  void setLongBreakIntervals(int cycles);

signals:
  void timeUpdated(QString time);
  void phaseChanged(bool isWork);
  void statsUpdated();

private slots:
  void onTick();

private:
  QTimer *timer;
  std::chrono::steady_clock::time_point endTime;
  int timeLeftSeconds;
  bool isRunning;
  bool isWorkPhase;
  int cycleCount;

  double workMinutes = 25.0;
  double shortBreakMinutes = 5.0;
  double longBreakMinutes = 15.0;
  int longBreakInterval = 4;

  void switchPhase();
};
