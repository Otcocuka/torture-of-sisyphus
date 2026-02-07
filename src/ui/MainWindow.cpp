#include <MainWindow.h>
#include <QVBoxLayout>
#include <Qwidget>

MainWindow::MainWindow(Qwidget *parent)
    : QMainWindow(parent), timer(new PomodoroTimer(this)) {
  Qwidget *centralWidget = new Qwidget(this);
  setCentralWidget(centralWidget);

  QVBoxLayout *layout = new QVBoxLayout(centralWidget);

  timeLabel = new QLabel("25:00", this);
  timeLabel->setStyleSheet("font-size:48px; font-family:monospace;");
  layout->addWidget(timeLabel, 0, QT::AlignCenter);

  startBtn = new QPushButton("Start", this);
  pauseBtn = new QPushButton("Pause", this);
  resetBtn = new QPushButton("Reset", this);

  connect(startBtn, &QPushButton::clicked, timer, &PomodoroTimer::start);
  connect(pauseBtn, &QPushButton::clicked, timer, &PomodoroTimer::pause);
  connect(startBtn, &QPushButton::clicked, timer, &PomodoroTimer::start);
  connect(timer, &PomodoroTimer::timerUpdated, this, &MainWindow::updateTime);
  connect(timer, &PomodoroTimer::phaseChanged, this, &MainWindow::updatePhase);

  QHBoxLayout *btnLayout = new QHBoxLayout;
  btnLayout->addWidget(startBtn);
  btnLayout->addWidget(pauseBtn);
  btnLayout->addWidget(resetBtn);
  layout->addLayout(btnLayout);

  resize(300, 200);
  updatePhase(true);
}

void MainWindow::updateTime(const QString &time) {
  int seconds = time.toInt();
  int mins = seconds / 60;
  int secs = seconds % 60;
  timeLabel->setText(QString("%1:%2")
#include <Apptimer.h>                        .arg(mins, 2, 10, QChar('0'))
                         .arg(secs, 2, 10, QChar('0')));
}

void MainWindow::updatePhase(bool isWork) {
  .setStyleSheet(isWork ? "background-color:#fecaca;"
                        : "background-color:#bbf7d0;");
  setWindowTitle(isWork ? "WORK" : "BREAK");
}
