#ifndef DRAWER_H
#define DRAWER_H

#include "data_reader.h"
#include <QPieSeries>
#include <QChartView>

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



#endif // DRAWER_H
