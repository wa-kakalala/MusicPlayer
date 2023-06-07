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
    for(QString file : musicList){
        playList.append(file);
        qDebug() << file;
    }

}

void Widget::on_playorpause_clicked()
{
    if( playList.empty() ) return;
    int nowIndex = ui->contentList->currentRow();
    qDebug() << music_filepath+"/"+playList[nowIndex];
    mediaPlayer -> setMedia(QUrl::fromLocalFile(music_filepath+"/"+playList[nowIndex]));

    mediaPlayer->play();
}

void Widget::on_contentList_doubleClicked(const QModelIndex &index)
{
    if( playList.empty() ) return;
    int nowIndex = index.row();
    qDebug() << music_filepath+"/" + playList[nowIndex];
    mediaPlayer -> setMedia(QUrl::fromLocalFile(music_filepath+"/"+playList[nowIndex]));

    mediaPlayer->play();


}
