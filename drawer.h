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
    virtual bool checkData(QList<unit> data)=0;



};


class CircleDrawer:public IDrawer
{
protected:
    bool checkData(QList<unit> data)
    {
        int i=0;
        data[i].value.toDouble();
        while(data[i].value.isValid() && i <data.size()-1)
        {
            i++;
            data[i].value.toDouble();
        }
        return data.size()-1==i;
    }
    void SetupData(QChartView *chartView, QList<unit> data)
    {
        if(checkData(data))
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
            chartView->chart()->setTitle("Circle Diagram");
        }
        else
        {
            chartView->chart()->setTitle("Wrong data into file");
        }
    }
};

class BarDrawer: public IDrawer
{
protected:
    bool checkData(QList<unit> data)
    {
        int i=0;
        data[i].value.toDouble();
        while(data[i].value.isValid() && i <data.size()-1)
        {
            i++;
            data[i].value.toDouble();
        }
        return data.size()-1==i;
    }
    void SetupData(QChartView* chartView,QList<unit> data)
    {
        if(checkData(data))
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
            chartView->chart()->setTitle("Bar Diagram");
        }
        else
        {
            chartView->chart()->setTitle("Wrong data into file");
        }

    }
};

class LineDrawer: public IDrawer
{
    bool checkData(QList<unit> data)
    {
        int i=0;
        data[i].key.toDouble();
        data[i].value.toDouble();
        while(data[i].key.isValid() && data[i].value.isValid() && i <data.size()-1)
        {
            i++;
            data[i].key.toDouble();
            data[i].value.toDouble();

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
            chartView->chart()->setTitle("Line Diagram");
        }
        else
        {
            chartView->chart()->setTitle("Wrong data into file");
        }
    }
};

#endif // DRAWER_H
