#pragma once

#include <QtWidgets/QMainWindow>
#include <QMediaPlaylist>
#include <QMediaPlayer>
#include <QVideoWidget>
#include <QPushButton>

class MediaPlayerV2 : public QMainWindow
{
	Q_OBJECT

public:
	MediaPlayerV2(QWidget *parent = Q_NULLPTR);

	void setupUi();
	void updateButtonState(const QMediaPlayer::State& state = QMediaPlayer::State::PlayingState);


	virtual QSize sizeHint() const override;

signals:

private slots:

private:

	QMediaPlayer *m_mediaPlayer;
	QMediaPlaylist * m_mediaPlaylist;
	QVideoWidget *m_videoWidget;
	QWidget * m_centralWidget;

	QPushButton *m_playButton;
	QPushButton *m_pauseButton;
	QPushButton *m_stopButton;

	QPushButton *m_nextButton;
	QPushButton *m_previousButton;
	QAction *m_openFileAction;
	void triggerMediaFileDialog();
};
