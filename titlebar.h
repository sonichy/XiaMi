#ifndef TITLEBAR_H
#define TITLEBAR_H

#include <QWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QMouseEvent>
#include <QAction>

class TitleBar : public QWidget
{
    Q_OBJECT

public:
    explicit TitleBar(QWidget *parent = nullptr);
    QPushButton *pushButton_search, *pushButton_lastPage, *pushButton_nextPage, *pushButton_minimize, *pushButton_maximize, *pushButton_close;
    QLineEdit *lineEdit_search, *lineEdit_page;
    QAction *action_set;

protected:
    bool eventFilter(QObject *obj, QEvent *event);

private:
    QPoint relativePos;
    bool MLBP;
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

signals:
    void moveMainWindow(QPoint);

private slots:
    void about();
};

#endif // TITLEBAR_H
