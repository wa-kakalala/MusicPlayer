#include "widget.h"
#include "ui_widget.h"


Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    default_music_filepath = QString("./music/");

    mediaPlayer = new QMediaPlayer(this);
    //mediaPlayer -> setMedia(QUrl::fromLocalFile());
    mediaPlayer->setVolume(100);

    connect(mediaPlayer,&QMediaPlayer::durationChanged,this,[=](qint64 duration){
        ui->playprogress->setRange(0,duration);
        ui->totalTime->setText(QString("%1:%2").arg(duration/1000/60,2,10,QLatin1Char('0')).arg(duration/1000%60,2,10,QLatin1Char('0')));
    });

    connect(mediaPlayer,&QMediaPlayer::positionChanged,this,[=](qint64 position){
       ui->playprogress->setValue(position);
       ui->currentTime->setText(QString("%1:%2").arg(position/1000/60,2,10,QLatin1Char('0')).arg(position/1000%60,2,10,QLatin1Char('0')));
    });
}

Widget::~Widget()
{
    delete mediaPlayer;
    delete ui;
}


void Widget::on_floder_clicked()
{
    music_filepath = QFileDialog::getExistingDirectory(this,QString("选择音乐文件夹"),default_music_filepath);
    QDir dir(music_filepath);
    QStringList musicList = dir.entryList(QStringList()<<"*.mp3"<<"*.wav");
    ui->contentList->addItems(musicList);
    ui->contentList->setCurrentRow(0);
    nowIndex = 0;
    for(QString file : musicList){
        playList.append(file);
        qDebug() << file;
    }
}

void Widget::on_playorpause_clicked()
{
    if( playList.empty() ) return;
    switch(mediaPlayer->state()){
        case QMediaPlayer::StoppedState:{
            int nowIndex = ui->contentList->currentRow();
            qDebug() << music_filepath+"/"+playList[nowIndex];
            mediaPlayer -> setMedia(QUrl::fromLocalFile(music_filepath+"/"+playList[nowIndex]));
            ui->playorpause->setStyleSheet(QStringLiteral("background-image:url(:/images/pause.png);"));
            mediaPlayer->play();
            break;
        }
        case QMediaPlayer::PlayingState:
            ui->playorpause->setStyleSheet(QStringLiteral("background-image:url(:/images/play.png);"));
            mediaPlayer->pause();
            break;
        case QMediaPlayer::PausedState:
            ui->playorpause->setStyleSheet(QStringLiteral("background-image:url(:/images/pause.png);"));
            mediaPlayer->play();
            break;
        default:
            break;
    }
}

void Widget::on_contentList_doubleClicked(const QModelIndex &index)
{
    if( playList.empty() ) return;
    nowIndex = index.row();
    qDebug() << music_filepath+"/" + playList[nowIndex];
    mediaPlayer -> setMedia(QUrl::fromLocalFile(music_filepath+"/"+playList[nowIndex]));
    ui->playorpause->setStyleSheet(QStringLiteral("background-image:url(:/images/pause.png);"));
    mediaPlayer->play();
}

void Widget::on_previous_clicked()
{
    if( playList.empty() ) return;
    nowIndex = (nowIndex + playList.size() - 1) % playList.size();
    ui->contentList->setCurrentRow(nowIndex);
    mediaPlayer -> setMedia(QUrl::fromLocalFile(music_filepath+"/"+playList[nowIndex]));
    ui->playorpause->setStyleSheet(QStringLiteral("background-image:url(:/images/pause.png);"));
    mediaPlayer->play();
}

void Widget::on_next_clicked()
{
    if( playList.empty() ) return;
    nowIndex = (nowIndex + 1) % playList.size();
    qDebug() << nowIndex;
    ui->contentList->setCurrentRow(nowIndex);
    mediaPlayer -> setMedia(QUrl::fromLocalFile(music_filepath+"/"+playList[nowIndex]));
    ui->playorpause->setStyleSheet(QStringLiteral("background-image:url(:/images/pause.png);"));
    mediaPlayer->play();
}

void Widget::on_playprogress_sliderReleased()
{
    mediaPlayer->setPosition(ui->playprogress->value());
}
