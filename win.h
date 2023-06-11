#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QLabel>
#include <QComboBox>
#include <QCheckBox>
#include <QPushButton>
#include <QSplitter>
#include <QChartView>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QBoxLayout>
#include <QListView>



#include <QtWidgets/QTextEdit>





class Win : public QWidget
{
    Q_OBJECT
    QPushButton* browse;
    QComboBox* graphic_type;
    QCheckBox* black_white;
    QPushButton* print;
    QSplitter* split;
    QListView* list;

    QTextEdit* text;//pass insted of graphic (charts)


    QWidget* top_bar;// pannel with bittons






public:
    Win(QWidget *parent = nullptr);
    ~Win();


};
#endif // WIDGET_H
