#include "titlebar.h"
#include <QHBoxLayout>
#include <QLabel>
#include <QDebug>
#include <QMenu>
#include <QAction>
#include <QApplication>
#include <QDialog>
#include <QIntValidator>

TitleBar::TitleBar(QWidget *parent) : QWidget(parent)
{
    MLBP = false;
    setStyleSheet("QPushButton::menu-indicator{ width:0px; }"
                  "QMenu::item:selected {background-color: #333333;}"
                  "QLineEdit { font-size:12px;  color:#cccccc; background-color:#000000; border:2px solid #000000; border-radius:10px;}"
                  "#lineEditSearch {  border-top-right-radius:0px; border-bottom-right-radius:0px; padding-left:10px;}"
                  "#pushButtonSearch { background-color:#000000; border-top-right-radius:10px; border-bottom-right-radius:10px; }");
    setFixedHeight(50);

    QHBoxLayout *hbox = new QHBoxLayout;
    hbox->setSpacing(0);

    QLabel *label_icon = new QLabel;
    label_icon->setPixmap(QPixmap(":/logo.png"));
    hbox->addWidget(label_icon);

    hbox->addStretch();

    lineEdit_search = new QLineEdit;
    lineEdit_search->setObjectName("lineEditSearch");
    lineEdit_search->setPlaceholderText("搜索音乐、歌手、歌词、用户");
    lineEdit_search->setFixedWidth(200);    
    hbox->addWidget(lineEdit_search);

    pushButton_search = new QPushButton;
    pushButton_search->setObjectName("pushButtonSearch");
    pushButton_search->setFixedSize(24,24);
    pushButton_search->setIcon(QIcon(":/search.svg"));
    pushButton_search->setIconSize(QSize(20,20));
    pushButton_search->setFlat(true);
    pushButton_search->setFocusPolicy(Qt::NoFocus);
    pushButton_search->setCursor(Qt::PointingHandCursor);
    pushButton_search->installEventFilter(this);
    hbox->addWidget(pushButton_search);

    pushButton_lastPage = new QPushButton;
    pushButton_lastPage->setFixedSize(24,24);
    pushButton_lastPage->setIcon(QIcon(":/lastpage.svg"));
    pushButton_lastPage->setIconSize(QSize(20,20));
    pushButton_lastPage->setFlat(true);
    pushButton_lastPage->setFocusPolicy(Qt::NoFocus);
    pushButton_lastPage->setCursor(Qt::PointingHandCursor);
    pushButton_lastPage->installEventFilter(this);
    hbox->addWidget(pushButton_lastPage);

    lineEdit_page = new QLineEdit;
    lineEdit_page->setObjectName("lineEditPage");
    lineEdit_page->setText("1");
    QValidator *validator = new QIntValidator(1,99,lineEdit_page);
    lineEdit_page->setValidator(validator);
    lineEdit_page->setFixedWidth(30);
    lineEdit_page->setAlignment(Qt::AlignCenter);
    hbox->addWidget(lineEdit_page);

    pushButton_nextPage = new QPushButton;
    pushButton_nextPage->setFixedSize(24,24);
    pushButton_nextPage->setIcon(QIcon(":/nextpage.svg"));
    pushButton_nextPage->setIconSize(QSize(20,20));
    pushButton_nextPage->setFlat(true);
    pushButton_nextPage->setFocusPolicy(Qt::NoFocus);
    pushButton_nextPage->setCursor(Qt::PointingHandCursor);
    pushButton_nextPage->installEventFilter(this);
    hbox->addWidget(pushButton_nextPage);

    hbox->addStretch();

    QPushButton *pushButton_menu = new QPushButton;
    pushButton_menu->setFixedSize(24,24);
    pushButton_menu->setIcon(QIcon(":/menu.svg"));
    pushButton_menu->setIconSize(QSize(20,20));
    pushButton_menu->setFlat(true);
    pushButton_menu->setFocusPolicy(Qt::NoFocus);
    pushButton_menu->setCursor(Qt::PointingHandCursor);
    QMenu *submenu = new QMenu(this);
    action_set = new QAction("设置",this);
    QAction *action_about = new QAction("关于",this);
    QAction *action_quit = new QAction("退出",this);
    submenu->addAction(action_set);
    submenu->addAction(action_about);
    submenu->addAction(action_quit);
    pushButton_menu->setMenu(submenu);
    connect(action_about,SIGNAL(triggered()),this,SLOT(about()));
    connect(action_quit,SIGNAL(triggered()),qApp,SLOT(quit()));
    hbox->addWidget(pushButton_menu);
    hbox->addSpacing(5);

    pushButton_minimize = new QPushButton;
    pushButton_minimize->setFixedSize(24,24);
    pushButton_minimize->setIcon(QIcon(":/minimize.svg"));
    pushButton_minimize->setIconSize(QSize(20,20));
    pushButton_minimize->setFlat(true);
    pushButton_minimize->setFocusPolicy(Qt::NoFocus);
    pushButton_minimize->setCursor(Qt::PointingHandCursor);
    pushButton_minimize->installEventFilter(this);
    hbox->addWidget(pushButton_minimize);
    hbox->addSpacing(5);

    pushButton_maximize = new QPushButton;
    pushButton_maximize->setFixedSize(24,24);
    pushButton_maximize->setIcon(QIcon(":/maximize.svg"));
    pushButton_maximize->setIconSize(QSize(20,20));
    pushButton_maximize->setFlat(true);
    pushButton_maximize->setFocusPolicy(Qt::NoFocus);
    pushButton_maximize->setCursor(Qt::PointingHandCursor);
    pushButton_maximize->installEventFilter(this);
    hbox->addWidget(pushButton_maximize);
    hbox->addSpacing(5);

    pushButton_close = new QPushButton;
    pushButton_close->setFixedSize(24,24);
    pushButton_close->setIcon(QIcon(":/close.svg"));
    pushButton_close->setIconSize(QSize(20,20));
    pushButton_close->setFlat(true);
    pushButton_close->setFocusPolicy(Qt::NoFocus);
    pushButton_close->setCursor(Qt::PointingHandCursor);
    pushButton_close->installEventFilter(this);
    hbox->addWidget(pushButton_close);

    setLayout(hbox);
}

void TitleBar::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton){
        MLBP = true;
        //qDebug() << "mousePress" << event->pos();
        relativePos = event->pos();
    }
}

void TitleBar::mouseMoveEvent(QMouseEvent *event)
{
    if(MLBP){
        setCursor(Qt::ClosedHandCursor);
        emit moveMainWindow(event->globalPos() - relativePos);
    }
}

void TitleBar::mouseReleaseEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
    MLBP = false;
    setCursor(Qt::ArrowCursor);
}

bool TitleBar::eventFilter(QObject *obj, QEvent *event)
{
    //qDebug() << obj->metaObject()->className();
    if ( QString(obj->metaObject()->className()) == "QPushButton" && event->type() == QEvent::MouseMove ) {
        return true;    // filter
    } else {
        return false;
    }
    // pass the event on to the parent class
    return QWidget::eventFilter(obj, event);
}

void TitleBar::about()
{
    QDialog *dialog = new QDialog(this);
    dialog->setWindowTitle("关于");
    dialog->setFixedSize(500,350);
    QVBoxLayout *vbox = new QVBoxLayout;
    QLabel *label = new QLabel;
    label->setPixmap(QPixmap(":/logo.png"));
    label->setAlignment(Qt::AlignCenter);
    label->setMargin(20);
    vbox->addWidget(label);
    label = new QLabel;
    label->setText("虾米音乐 V1.0");
    label->setAlignment(Qt::AlignCenter);
    label->setStyleSheet("font-size:15px;");
    vbox->addWidget(label);
    label = new QLabel;
    label->setText("         一款基于 Qt 的虾米音乐客户端。\n作者：黄颖\nE-mail: sonichy@163.com\n主页：https://github.com/sonichy\n音乐版权：虾米音乐\n参考：\nhttps://github.com/listen1/listen1_chrome_extension");
    label->setStyleSheet("font-size:15px;");
    label->setWordWrap(true);
    label->setAlignment(Qt::AlignTop);
    vbox->addWidget(label);
    vbox->addStretch();
    dialog->setLayout(vbox);
    dialog->show();
}
