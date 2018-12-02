#include "MediaPlayerV2.h"
#include <QDebug>
#include <QMenuBar>
#include <QFileDialog>
#include <QHBoxLayout>
#include <QGridLayout>

MediaPlayerV2::MediaPlayerV2(QWidget *parent)
	: QMainWindow(parent),
	m_mediaPlayer(new QMediaPlayer(this)),
	m_mediaPlaylist(new QMediaPlaylist(m_mediaPlayer)),
	m_videoWidget(new QVideoWidget(this)),
	m_centralWidget(new QWidget(this)),
	m_playButton(new QPushButton("Play", this)),
	m_pauseButton(new QPushButton("Pause", this)),
	m_stopButton(new QPushButton("Stop", this)),
	m_nextButton(new QPushButton("Next", this)),
	m_previousButton(new QPushButton("Previous", this))
{
	m_mediaPlayer->setPlaylist(m_mediaPlaylist);
	m_mediaPlayer->setVideoOutput(m_videoWidget);

	setupUi();
	setCentralWidget(m_centralWidget);

	connect(m_playButton, &QPushButton::clicked, m_mediaPlayer, &QMediaPlayer::play);
	connect(m_pauseButton, &QPushButton::clicked, m_mediaPlayer, &QMediaPlayer::pause);
	connect(m_stopButton, &QPushButton::clicked, m_mediaPlayer, &QMediaPlayer::stop);
	connect(m_nextButton, &QPushButton::clicked, m_mediaPlaylist, &QMediaPlaylist::next);
	connect(m_previousButton, &QPushButton::clicked, m_mediaPlaylist, &QMediaPlaylist::previous);

	connect(m_mediaPlayer, &QMediaPlayer::stateChanged, [this]() {updateButtonState(); });
	updateButtonState(QMediaPlayer::StoppedState);
	m_openFileAction = menuBar()->addAction("Open File");
	connect(m_openFileAction, &QAction::triggered, [this]() {triggerMediaFileDialog(); });
}

void MediaPlayerV2::setupUi()
{
	qDebug() << "Setup UI";
	QGridLayout *displayLayout = new QGridLayout(this);
	displayLayout->addWidget(m_videoWidget, 0, 0);

	QGridLayout *buttonBar = new QGridLayout(this);
	buttonBar->setMargin(0);
	buttonBar->addWidget(m_previousButton, 1, 0);
	buttonBar->addWidget(m_nextButton, 1, 1);
	buttonBar->addWidget(m_playButton, 1, 2);
	buttonBar->addWidget(m_stopButton, 1, 3);
	buttonBar->addWidget(m_pauseButton, 1, 4);

	displayLayout->addItem(buttonBar, 1, 0);
	m_centralWidget->setLayout(displayLayout);
}

void MediaPlayerV2::updateButtonState(const QMediaPlayer::State& state)
{
	qDebug() << "Update Button State";
}

QSize MediaPlayerV2::sizeHint() const
{
	return { 800, 800 };
}

void MediaPlayerV2::triggerMediaFileDialog()
{
	qDebug() << "Trigger Media File Dialog";
	QStringList filePaths = QFileDialog::getOpenFileNames(this, "Select one/more files to open");

	for (const auto& path : filePaths)
	{
		m_mediaPlaylist->addMedia(QUrl::fromLocalFile(path));
	}

	if (m_mediaPlaylist->currentIndex() == -1)
	{
		m_mediaPlaylist->setCurrentIndex(0);
	}
}
