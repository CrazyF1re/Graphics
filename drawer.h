#ifndef DRAWER_H
#define DRAWER_H

#include "data_reader.h"
#include <QPieSeries>
#include <QChartView>

#include <QBarSeries>
#include <QBarSet>

#include <QLineSeries>
#include <QValueAxis>
//Using template pattern to use defferent types of diagrams
class IDrawer
{
public:
    void draw(QList<unit> data, QChartView* chartView)// set up steps will repit
    {
        //clear field
        chartView->chart()->removeAllSeries();
        //setup data into chart
        SetupData(chartView,data);

        chartView->chart()->setAnimationOptions(QChart::SeriesAnimations);
        chartView->setRenderHint(QPainter::Antialiasing);

        //update data and show it at window
        chartView->update();


    }
    virtual ~IDrawer(){}
protected:
    virtual void SetupData(QChartView* chartView,QList<unit> data)=0;//set up data into char viewer
    // ???  virtual void SetupDiagram(QChartView* chart);//set up type of diagram

};


class CircleDrawer:public IDrawer
{
protected:
    void SetupData(QChartView *chartView, QList<unit> data)
    {
        QPieSeries* series = new QPieSeries();
        for(unit& piece : data)
        {
            if(data.indexOf(piece)==30)break;
            QString key  = piece.key.toString();
            double value = piece.value.toDouble();
            series->append(key,value);
        }

        chartView->chart()->addSeries(series);
    }
};

class BarDrawer: public IDrawer
{
protected:
    void SetupData(QChartView* chartView,QList<unit> data)
    {
        QBarSeries* series = new QBarSeries();

        for(unit& piece : data)
        {
            if(data.indexOf(piece)==30)break;
            QString key  = piece.key.toString();
            double value = piece.value.toDouble();

            QBarSet* set = new QBarSet(key);
            *set<<value;
            series->append(set);
        }
        chartView->chart()->addSeries(series);

    }
};

class LineDrawer: public IDrawer
{
    bool checkData(QList<unit> data)
    {
        int i=0;
        while(data[i].key.canConvert( QVariant::Double) && data[i].value.canConvert(QVariant::Double )&& i <data.size()-1)
        {
            i++;
        }
        return data.size()-1==i;
    }

protected:
    void SetupData(QChartView* chartView,QList<unit> data)
    {

        if(checkData(data))
        {
            QLineSeries* series = new QLineSeries();

            for(unit& piece:data)
            {

                series->append(piece.key.toDouble(),piece.value.toDouble());

            }
            chartView->chart()->addSeries(series);
        }
    }
};

#endif // DRAWER_H
