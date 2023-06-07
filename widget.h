#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QFileDialog>
#include <QDir>
#include <QDebug>
#include <QMediaPlayer>
#include <QAudioOutput>
#include <QUrl>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void on_floder_clicked();

    void on_playorpause_clicked();

    void on_contentList_doubleClicked(const QModelIndex &index);

    void on_previous_clicked();

    void on_next_clicked();

    void on_playprogress_sliderReleased();

private:
    Ui::Widget *ui;
    QString default_music_filepath;
    QMediaPlayer* mediaPlayer;
    QString music_filepath;
    QStringList playList;
    qint16      nowIndex;
};
#endif // WIDGET_H
