#include "AppTimer.h"

#include <QDateTime>
#include <QDebug>
#include <atomic>
#include <chrono>

PomodoroTimer::PomodoroTimer(QObject *parent)
    : QObject(parent), timer(new QTimer(this)), timeLeftSeconds(0),
      isRunning(false), isWorkPhase(true), cycleCount(0) {
  connect(timer, &QTimer::timeout, this, &PomodoroTimer::onTick);
}

void PomodoroTimer::start() {
  if (!isRunning) {
    isRunning = true; // Ensure the entire calculation is wrapped in parenthesis
                      // and the colon is added
    int duration =
        static_cast<int>(isWorkPhase ? workMinutes * 60
                                     : ((cycleCount % longBreakInterval == 0)
                                            ? longBreakMinutes * 60
                                            : shortBreakMinutes * 60));

    timeLeftSeconds = duration;
    endTime = std::chrono::steady_clock::now() + std::chrono::seconds(duration);
    timer->start(1000);
    emit timeUpdated(QString::number(timeLeftSeconds));
    emit phaseChanged(isWorkPhase);
  }
}

void PomodoroTimer::pause() {
  if (isRunning) {
    isRunning = false;
    timer->stop();
  }
}

void PomodoroTimer::reset() {
  timer->stop();
  isRunning = false;
  isWorkPhase = true;
  cycleCount = 0;
  timeLeftSeconds = static_cast<int>(workMinutes * 60);
  emit timeUpdated(QString::number(timeLeftSeconds));
  emit phaseChanged(true);
}

void PomodoroTimer::setWorkMinutes(double mins) {
  workMinutes = mins;
  if (!isRunning && isWorkPhase) {
    reset();
  }
}

void PomodoroTimer::onTick() {
  auto now = std::chrono::steady_clock::now();

  auto remaining =
      std::chrono::duration_cast<std::chrono::seconds>(endTime - now).count();

  if (remaining <= 0) {
    switchPhase();
    return;
  }
  timeLeftSeconds = static_cast<int>(remaining);
  emit timeUpdated(QString::number(timeLeftSeconds));
}

void PomodoroTimer::switchPhase() {
  isRunning = false;
  timer->stop();

  isWorkPhase = !isWorkPhase;
  if (isWorkPhase) {
    cycleCount++;
  }

  emit phaseChanged(isWorkPhase);
  start();
}
